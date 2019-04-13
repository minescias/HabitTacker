#include <Core/Utils/Strings/Case.h>

#include <algorithm>
#include <locale>

namespace Strings
{

void lower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

std::string lower_copy(const std::string& str)
{
    std::string tmp = str;
    lower(tmp);
    return tmp;
}

}
