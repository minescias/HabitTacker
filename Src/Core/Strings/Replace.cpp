#include "Core/Strings/Replace.h"

namespace Strings
{

std::string replaceAllCopy(const std::string& source,
    const std::string& from, const std::string& to)
{
    auto result = source;
    auto lastFound = std::size_t{0};

    while (true)
    {
        auto pos = result.find(from, lastFound);

        if (pos == std::string::npos)
            return result;

        result.replace(pos, from.size(), to);
        lastFound = pos + to.size();
    }
    return result;
}

} // namespace Strings
