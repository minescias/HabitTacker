#ifndef __VALUE_GETTER_H
#define __VALUE_GETTER_H

#include <string>
#include <string_view>

#include <Core/Types/IsOptional.h>

namespace Db
{
namespace Detail
{
template<typename T>
T getVal(std::string_view columnName, const std::string& value);

} // namespace Detail

template<typename T>
T getVal(std::string_view columnName, const std::string& value)
{
	if constexpr (Types::isOptional_v<T>)
	{
		if (value.empty())
			return std::nullopt;

		return std::make_optional(
			Detail::getVal<typename T::value_type>(columnName, value));
	}
	else
		return Detail::getVal<T>(columnName, value);
}

} // namespace Db

#endif // __VALUE_GETTER_H
