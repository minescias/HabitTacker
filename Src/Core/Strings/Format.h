#ifndef __FORMAT_H
#define __FORMAT_H

#include <string>

namespace Strings
{

} // namespace Strings

// template<typename T, typename... TArgs>
// std::string format()

std::string format(const std::string& str, const std::string& val = "")
{
	auto pos = str.find("%1%");
	auto tmp = str;
	
	if (pos != std::string::npos)
		tmp = tmp.replace(pos, 3, val);	

	return tmp;
}

#endif // __FORMAT_H
