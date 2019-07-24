#include "Core/Database/Parameters.h"

#include <ctime>
#include <string_view>

#include <Libraries/SQLite/sqlite3.h>

#include <Core/Logger/Log.h>
#include <Core/Strings/Format.h>
#include <Core/Database/Database.h>
#include <Core/Utils/Exceptions/LogicError.h>

namespace
{

template<typename T>
void logParamIsSet(std::string_view name, T value, sqlite3_stmt* statement)
{
    log(Strings::format("Query %1%: parameter %2% set to %3%", 
        std::addressof(*statement), name, value), Log::Levels::Sql);
}

} // namespace

namespace Db
{

Parameters::Parameters(Db::Database* db, sqlite3_stmt* statement)
    : statement(statement)
{
    createUnsetParametersList();
}

template<>
void Parameters::setParam(const std::string& name, std::string value)
{
    auto index = getParamIndex(name);
    auto dbStatus = sqlite3_bind_text(statement, index, value.c_str(),
        value.size(), SQLITE_TRANSIENT);

    checkForDbError(dbStatus);
    removeFromUnsetParamsList(name);
    logParamIsSet(name, value, statement);
}

template<>
void Parameters::setParam(const std::string& name, const char* value)
{
    setParam(name, std::string(value));
}

template<>
void Parameters::setParam(const std::string& name, int value)
{
    logParamIsSet(name, value, statement);
    auto index = getParamIndex(name);
    auto dbStatus = sqlite3_bind_int(statement, index, value);

    checkForDbError(dbStatus);
    removeFromUnsetParamsList(name);
    logParamIsSet(name, value, statement);
}

template<>
void Parameters::setParam(const std::string& name, time_t value)
{
    auto index = getParamIndex(name);
    auto dbStatus = sqlite3_bind_int64(statement, index, value);

    checkForDbError(dbStatus);
    removeFromUnsetParamsList(name);
    logParamIsSet(name, value, statement);
}

template<>
void Parameters::setParam(const std::string& name, double value)
{
    auto index = getParamIndex(name);
    auto dbStatus = sqlite3_bind_double(statement, index, value);

    checkForDbError(dbStatus);
    removeFromUnsetParamsList(name);
    logParamIsSet(name, value, statement);
}

void Parameters::createUnsetParametersList()
{
    auto paramsCount = sqlite3_bind_parameter_count(statement);
    if (paramsCount == 0)
        return;

    for (int i=1; i<=paramsCount; ++i)
        unsetParams.insert(sqlite3_bind_parameter_name(statement, i));
}

void Parameters::removeFromUnsetParamsList(const std::string& name)
{
    unsetParams.erase(name);
}

void Parameters::ensureAllParamsAreSet()
{
    if (unsetParams.empty())
        return;

    auto paramName = *unsetParams.begin();
    auto message = "Query: parameter " + paramName + " is not set";
    throw LogicError(message);
}

int Parameters::getParamIndex(const std::string& name)
{
    auto index = sqlite3_bind_parameter_index(statement, name.c_str());

    if (index == 0) // param not found
        throw LogicError("Could not find parameter " + name);

    return index;
}

void Parameters::checkForDbError(int dbStatus)
{
    if (dbStatus != SQLITE_OK)
        throw LogicError(sqlite3_errmsg(db->getHandler()));
}

} // namespace Db




