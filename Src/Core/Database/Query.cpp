#include "Core/Database/Query.h"

#include "sqlite/sqlite3.h"

#include "Core/Database/Database.h"
#include "Core/Exceptions/LogicError.h"
#include "Core/Logger/Log.h"

namespace Db
{
Query::Query(Database* database, const std::string& sql) : database(database)
{
	auto dbStatus = sqlite3_prepare_v2(
		database->getHandler(), sql.c_str(), sql.size(), &statement, nullptr);

	checkForDbError(dbStatus);
	parameters = std::make_unique<Parameters>(database, statement);

	log(Log::Levels::Sql, "Query {} prepared with \"{}\"", fmt::ptr(statement), sql);
}

Query::~Query()
{
	finalizeStatement();
}

void Query::executeCommand()
{
	auto dbStatus = runQuery();

	if (dbStatus == SQLITE_ROW)
		throw LogicError("Db: Query returned a value while executing command");

	if (dbStatus != SQLITE_DONE)
		checkForDbError(dbStatus);
}

Dataset Query::execute()
{
	auto dbStatus = runQuery();
	auto columnsCount = sqlite3_column_count(statement);
	Dataset dataset;

	for (auto currentColumn = 0; currentColumn < columnsCount; ++currentColumn)
		dataset.addColumn(sqlite3_column_name(statement, currentColumn));

	while (dbStatus == SQLITE_ROW)
	{
		auto row = dataset.addRow();

		for (auto currentColumn = 0; currentColumn < columnsCount; ++currentColumn)
		{
			char* value = (char*)sqlite3_column_text(statement, currentColumn);

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

	log(Log::Levels::Sql, "Query {} executed", fmt::ptr(statement));

	return sqlite3_step(statement);
}

void Query::checkForDbError(int dbStatus)
{
	using namespace std::string_literals;

	if (dbStatus != SQLITE_OK)
	{
		finalizeStatement();
		throw LogicError("Db: "s + sqlite3_errmsg(database->getHandler()));
	}
}

void Query::finalizeStatement()
{
	if (statement)
	{
		auto dbStatus = sqlite3_finalize(statement);
		statement = nullptr;
		checkForDbError(dbStatus);

		log(Log::Levels::Sql, "Query {} unprepared", fmt::ptr(statement));
	}
}

} // namespace Db
