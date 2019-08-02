#ifndef __VALUE_GETTER_H
#define __VALUE_GETTER_H

#include <string>
#include <string_view>

namespace Db
{

template<typename T>
T getVal(std::string_view columnName, const std::string& value);
// string_view does not work with stoi :(

} // namespace Db

#endif // __VALUE_GETTER_H
