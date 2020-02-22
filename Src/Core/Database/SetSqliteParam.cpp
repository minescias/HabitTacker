#include "Core/Database/SetSqliteParam.h"

#include "sqlite/sqlite3.h"

#include "Core/DateTime/Date.h"

namespace Db::Detail
{
template<>
int setSqliteParam(sqlite3_stmt* statement, int index, std::nullptr_t)
{
	return sqlite3_bind_null(statement, index);
}

template<>
int setSqliteParam(sqlite3_stmt* statement, int index, std::nullopt_t)
{
	return sqlite3_bind_null(statement, index);
}

template<>
int setSqliteParam(sqlite3_stmt* statement, int index, std::string value)
{
	return sqlite3_bind_text(
		statement, index, value.c_str(), value.size(), SQLITE_TRANSIENT);
}

template<>
int setSqliteParam(sqlite3_stmt* statement, int index, const char* value)
{
	std::string tmpString = value;
	return sqlite3_bind_text(
		statement, index, tmpString.c_str(), tmpString.size(), SQLITE_TRANSIENT);
}

template<>
int setSqliteParam(sqlite3_stmt* statement, int index, int value)
{
	return sqlite3_bind_int(statement, index, value);
}

template<>
int setSqliteParam(sqlite3_stmt* statement, int index, double value)
{
	return sqlite3_bind_double(statement, index, value);
}

template<>
int setSqliteParam(sqlite3_stmt* statement, int index, Dt::Date value)
{
	return sqlite3_bind_int(
		statement, index, date::sys_days{value}.time_since_epoch().count());
}

} // namespace Db::Detail
