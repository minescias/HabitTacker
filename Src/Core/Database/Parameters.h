#ifndef __PARAMETERS_H
#define __PARAMETERS_H

#include <set>
#include <string>
#include <type_traits>

#include <Core/Database/Database_fwd.h>
#include <Core/Database/SQLite_fwd.h>
#include <Core/Format/DateFormatter.h>
#include <Core/Format/OptionalFormatter.h>
#include <Core/Logger/Log.h>
#include <Core/Types/IsOptional.h>

namespace Db
{
class Parameters
{
public:
	Parameters(Db::Database* db, sqlite3_stmt* statement);
	void ensureAllParamsAreSet();

	template<typename T>
	void setParam(const std::string& name, T value)
	{
		auto index = getParamIndex(name);
		auto dbStatus = setSqliteParam2(index, value);

		checkForDbError(dbStatus);
		removeFromUnsetParamsList(name);
		logParamIsSet(name, value, statement);
	}

private:
	template<typename T>
	int setSqliteParam(int index, T value);

	template<typename T>
	void logParamIsSet(std::string_view name, T value, sqlite3_stmt* statement)
	{
		log(Log::Levels::Sql,
			"Query {}: parameter {} set to {}",
			fmt::ptr(statement),
			name,
			value);
	}

	template<typename T>
	int setSqliteParam2(int index, T value)
	{
		if constexpr (Types::isOptional_v<T>)
		{
			if (value.has_value())
				return setSqliteParam(index, *value);
			else
				return setSqliteParam(index, nullptr);
		}
		else if (std::is_same_v<T, std::nullopt_t>)
		{
			return setSqliteParam(index, nullptr);
		}
		else
			return setSqliteParam(index, value);
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
