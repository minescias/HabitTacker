#ifndef __FORMAT_H
#define __FORMAT_H

#include <string>
#include <sstream>

#include <Core/Utils/Exceptions/LogicError.h>

namespace Strings
{

namespace Detail
{

inline std::string getIdentifier(int index)
{
	return std::string("%") + std::to_string(index) + "%";
}

template<typename T>
std::string format(const std::string& str, int index,  T value)
{
	auto tmpStr = str;
	auto identifier = getIdentifier(index);
	
	auto pos = tmpStr.find(identifier);
	if (pos == std::string::npos)
		throw LogicError("Strings::format: more variables than placeholders");


	while (pos != std::string::npos)
	{
		std::stringstream ss;
		ss << tmpStr.substr(0, pos) << value << tmpStr.substr(pos + 3);
		tmpStr = ss.str();

		pos = tmpStr.find(identifier);
	}

	return tmpStr;
}

template<typename T, typename... TArgs>
std::string format(const std::string& str, int index,  T value, TArgs... args)
{
	auto tmpStr = format (str, index, value);
	return format(tmpStr, index + 1, args...);
}

} // namespace Detail

inline std::string format(const std::string& str)
{
	return str;
}

template <typename... TArtgs>
std::string format(const std::string& str, TArtgs... targs)
{
	return Detail::format(str, 1, targs...);
}

} // namespace Strings

#endif // __FORMAT_H
