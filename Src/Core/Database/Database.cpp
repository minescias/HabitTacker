#include "Core/Database/Database.h"

#include "sqlite/sqlite3.h"

#include "Core/Logger/Log.h"
#include "Core/Exceptions/LogicError.h"

namespace
{

const std::string dbError = "Database error: ";

} // namespace

namespace Db
{

Database::Database(const std::string& name)
    : handler(nullptr)
    , databaseName(name)
{
    connect(databaseName);
}

Database::~Database()
{
    disconnect();
}

void Database::connect(const std::string& name)
{
    auto dbStatus = 0;

    dbStatus = sqlite3_open(name.c_str(), &handler);

    if (dbStatus != SQLITE_OK)
        throw LogicError(dbError + sqlite3_errstr(dbStatus));

    log(Log::Levels::Sql, "Connected to dabase '" + name + "'");
}

void Database::disconnect()
{
    auto dbStatus = 0;

    dbStatus = sqlite3_close(handler);

    if (dbStatus != SQLITE_OK)
        throw LogicError(dbError + sqlite3_errstr(dbStatus));

    log(Log::Levels::Sql, "Disconnected from dabase '" + databaseName + "'");
}

sqlite3* Database::getHandler()
{
    return handler;
}

} // namespace Db
