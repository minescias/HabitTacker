#ifndef __FORMAT_H
#define __FORMAT_H

#include <string>
#include <sstream>

namespace Strings::Detail
{

std::string getIdentifier(int index)
{
	return std::string("%") + std::to_string(index) + "%";
}

template<typename T>
std::string format(const std::string& str, int index,  T value)
{
	auto pos = str.find(getIdentifier(index));
	std::stringstream ss;
	ss << str.substr(0, pos) << value << str.substr(pos + 3);
	return ss.str();
}

template<typename T, typename... TArgs>
std::string format(const std::string& str, int index,  T value, TArgs... args)
{
	auto pos = str.find(getIdentifier(index));
	std::stringstream ss;
	ss << str.substr(0, pos) << value << str.substr(pos + 3);
	return format(ss.str(), index + 1, args...);
}

} // namespace Strings::Detail

std::string format(const std::string& str)
{
	return str;
}

template <typename... TArtgs>
std::string format(const std::string& str, TArtgs... targs)
{
	return Strings::Detail::format(str, 1, targs...);
}

#endif // __FORMAT_H
