#include "Core/Database/ValueGetter.h"

#include "string"

#include "Core/Strings/Format.h"
#include "Core/Utils/Exceptions/LogicError.h"
#include "Core/Utils/Types/TypeNames.h"

namespace
{

template<typename  T>
using  CastFunction = T (const std::string&);

template<typename  T>
T tryToCast(std::string_view name, const std::string& value, 
    CastFunction<T>* castFuncion)
{
    try
    {
        return castFuncion(value);
    }
    catch(std::logic_error& err)
    {
        throw LogicError(Strings::format(
            "Db: Cannot cast value '%1%' of column '%2%' to type %3%", 
             value, name, getTypeName(typeid(T).hash_code())));
    }
}

template<typename T>
void assertValueIsNotEmpty(std::string_view name, std::string_view value)
{
    if (value.empty())
    {
        throw LogicError(Strings::format(
            "Db: Cannot cast null value of column '%1%' to type %2%", 
            name, getTypeName(typeid(T).hash_code())));
    }
}

} // namespace

namespace Db
{

template<>
std::string getVal<std::string>(std::string_view columnName, const std::string& value)
{
	return std::string(value);
}

template<>
int getVal<int>(std::string_view columnName, const std::string& value)
{
    assertValueIsNotEmpty<int>(columnName, value);
	auto castFunc = [](const std::string& value){return stoi(value);};
    return tryToCast<int>(columnName, value, castFunc);
}

template<>
double getVal<double>(std::string_view columnName, const std::string& value)
{
    assertValueIsNotEmpty<double>(columnName, value);
	auto castFunc = [](const std::string& value){return stod(value);};
    return tryToCast<double>(columnName, value, castFunc);
}

template<>
time_t getVal<time_t>(std::string_view columnName, const std::string& value)
{
    assertValueIsNotEmpty<time_t>(columnName, value);
    auto castFunc = [](const std::string& value){return stol(value);};
    return tryToCast<time_t>(columnName, value, castFunc);
}

} // namespace Db
