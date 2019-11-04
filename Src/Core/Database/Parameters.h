#ifndef __PARAMETERS_H
#define __PARAMETERS_H

#include <set>
#include <string>

#include <Core/Database/Database_fwd.h>
#include <Core/Database/SQLite_fwd.h>
#include <Core/Logger/Log.h>
#include <Core/Strings/Format.h>

namespace Db
{
class Parameters
{
public:
	Parameters(Db::Database* db, sqlite3_stmt* statement);
	void ensureAllParamsAreSet();

	template<typename T> void setParam(const std::string& name, T value)
	{
		auto index = getParamIndex(name);
		auto dbStatus = setSqliteParam(index, value);

		checkForDbError(dbStatus);
		removeFromUnsetParamsList(name);
		logParamIsSet(name, value, statement);
	}

private:
	template<typename T> int setSqliteParam(int index, T value);

	template<typename T>
	void logParamIsSet(std::string_view name, T value, sqlite3_stmt* statement)
	{
		log(Log::Levels::Sql,
			Strings::format(
				"Query %1%: parameter %2% set to %3%",
				std::addressof(*statement),
				name,
				value));
	}

	void createUnsetParametersList();
	void removeFromUnsetParamsList(const std::string& name);
	int getParamIndex(const std::string& name);
	void checkForDbError(int dbStatus);

private:
	sqlite3_stmt* statement;
	std::set<std::string> unsetParams;
	Db::Database* db;
};

} // namespace Db

#endif // __PARAMETERS_H
