#ifndef __SET_SQLITE_PARAM_H
#define __SET_SQLITE_PARAM_H

#include <Core/Database/SQLite_fwd.h>
#include <Core/Types/IsOptional.h>

namespace Db
{
namespace Detail
{
template<typename T>
int setSqliteParam(sqlite3_stmt* stmt, int index, T value);

} // namespace Detail

template<typename T>
int setSqliteParam(sqlite3_stmt* stmt, int index, T value)
{
	if constexpr (Types::isOptional_v<T>)
	{
		if (value.has_value())
			return Detail::setSqliteParam(stmt, index, *value);
		else
			return Detail::setSqliteParam(stmt, index, nullptr);
	}

	return Detail::setSqliteParam(stmt, index, value);
}

} // namespace Db

#endif // __SET_SQLITE_PARAM_H
