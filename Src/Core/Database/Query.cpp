#include "Core/Database/Query.h"

#include <Libraries/SQLite/sqlite3.h>

#include "Core/Database/Database.h"
#include "Core/Database/Dataset.h"
#include "Core/Logger/Log.h"
#include "Core/Strings/Format.h"
#include "Core/Utils/Exceptions/LogicError.h"

namespace Db
{

Query::Query(Database* database, const std::string& sql)
    :database(database)
{
    auto dbStatus = sqlite3_prepare_v2(database->getHandler(), sql.c_str(),
        sql.size(), &statement, nullptr);
    
    checkForDbError(dbStatus);
    parameters = std::make_unique<Parameters>(database, statement);
    
    log(Strings::format("Query %1% prepared with %2%",
        std::addressof(*statement), sql), Log::Levels::Sql);
}

Query::~Query()
{
    auto dbStatus = sqlite3_finalize(statement);
    checkForDbError(dbStatus);

    log(Strings::format("Query %1% unprepared", std::addressof(*statement)),
        Log::Levels::Sql);
}

std::unique_ptr<Dataset> Query::execute()
{
    auto dbStatus = runQuery();
    std::unique_ptr<Dataset> dataset = std::make_unique<Dataset>();

    if (!dataset->initialized())
        setDatasetColumns(dataset.get());

    while (dbStatus == SQLITE_ROW)
    {
        addDatasetRow(dataset.get());
        dbStatus = sqlite3_step(statement);
    }

    if (dbStatus == SQLITE_DONE)
        return dataset;

    if (dbStatus != SQLITE_ROW && dbStatus != SQLITE_DONE)
        checkForDbError(dbStatus);

    return dataset;
}

void Query::executeCommand()
{
    auto dbStatus = runQuery();    

    if(dbStatus == SQLITE_ROW)
        throw LogicError("Db: Query returned a value while executing command");

    if (dbStatus != SQLITE_DONE)
        checkForDbError(dbStatus);
}

Dataset2 Query::execute2()
{
    auto dbStatus = runQuery();
    auto columnsCount = sqlite3_column_count(statement);
    Dataset2 dataset;

    for (auto currentColumn = 0; currentColumn < columnsCount; ++currentColumn)
        dataset.addColumn(sqlite3_column_name(statement, currentColumn));    

    while (dbStatus == SQLITE_ROW)
    {
        auto row = dataset.addRow();

        for (auto currentColumn = 0; currentColumn < columnsCount; ++currentColumn)
        {
            char* value = (char*)sqlite3_column_text(statement, currentColumn);
            auto name = sqlite3_column_name(statement, currentColumn);

            if (value)
                row->set(sqlite3_column_name(statement, currentColumn), value);
        }

        dbStatus = sqlite3_step(statement);
    }

    if (dbStatus == SQLITE_DONE)
        return dataset;

    if (dbStatus != SQLITE_ROW && dbStatus != SQLITE_DONE)
        checkForDbError(dbStatus);

    return dataset;
}

int Query::runQuery()
{
    parameters->ensureAllParamsAreSet();
    return sqlite3_step(statement);

    log(Strings::format("Query %1% executed", 
        std::addressof(*statement)), Log::Levels::Sql);
}

void Query::setDatasetColumns(Dataset* dataset)
{
    auto columnsCount = sqlite3_column_count(statement);

    for (auto currentColumn = 0; currentColumn < columnsCount; ++currentColumn)
        dataset->addColumn(sqlite3_column_name(statement, currentColumn));
}

void Query::addDatasetRow(Dataset* dataset)
{
    auto columnsCount = sqlite3_column_count(statement);
    auto currentRow = Dataset::Row();

    for (auto currentColumn = 0; currentColumn < columnsCount; ++currentColumn)
    {
        char* value = (char*)sqlite3_column_text(statement, currentColumn);
        if (value)
            currentRow.push_back(value);
        else
            currentRow.push_back(std::string());
    }

    dataset->addRow(currentRow);
}

void Query::checkForDbError(int dbStatus)
{
    using namespace std::string_literals;

    if (dbStatus != SQLITE_OK)
        throw LogicError("Db: "s +  sqlite3_errmsg(database->getHandler()));
}

} // namespace Db
