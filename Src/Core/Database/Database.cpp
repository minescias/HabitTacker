#include "Core/Database/Database.h"

#include <iostream>
#include <Libraries/SQLite/sqlite3.h>
#include "Core/Utils/Exceptions/LogicError.h"
#include "Core/Utils/Logger/Log.h"

namespace
{
//dupa
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

    if (dbStatus == SQLITE_OK)
        log ("Database " + databaseName + " opened");
    else
        throw LogicError(dbError + sqlite3_errstr(dbStatus));
}

void Database::disconnect()
{
    auto dbStatus = 0;

    dbStatus = sqlite3_close(handler);

    if (dbStatus == SQLITE_OK)
        log ("Database " + databaseName  + " closed");
    else
        throw LogicError(dbError + sqlite3_errstr(dbStatus));
}

sqlite3* Database::getHandler()
{
    return handler;
}

} // namespace Db
