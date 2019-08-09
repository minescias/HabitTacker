#include <Core/Strings/Compare.h>

#include <Core/Exceptions/LogicError.h>

namespace Strings
{

bool startsWith(const std::string& source, const std::string& matcher)
{
    if (matcher.empty())
        return true;

    if (source.empty())
        throw LogicError("Strings::startsWith: source is empty");

    auto sourceBeginning = source.substr(0, matcher.length());
    return sourceBeginning == matcher;
}

} // Strings
