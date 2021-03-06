#include "Core/Database/Parameters.h"

#include <string_view>

#include "sqlite/sqlite3.h"

#include "Core/Database/Database.h"
#include "Core/Exceptions/LogicError.h"

namespace Db
{
Parameters::Parameters(Db::Database* db, sqlite3_stmt* statement)
	: statement(statement)
{
	createUnsetParametersList();
}

void Parameters::createUnsetParametersList()
{
	auto paramsCount = sqlite3_bind_parameter_count(statement);
	if (paramsCount == 0)
		return;

	for (int i = 1; i <= paramsCount; ++i)
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
