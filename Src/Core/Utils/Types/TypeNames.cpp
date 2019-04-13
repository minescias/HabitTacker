#include "Core/Utils/Types/TypeNames.h"

#include <typeinfo>

std::string getTypeName(std::size_t typeId)
{
    if (typeId == typeid(int).hash_code())
        return "int";

    if (typeId == typeid(double).hash_code())
        return "double";

    if (typeId == typeid(std::string).hash_code())
        return "std::string";
}
