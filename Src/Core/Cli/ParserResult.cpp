#include "Core/Cli/ParserResult.h"

namespace Cli
{

ParserResult::ParserResult()
{
}

void ParserResult::setCommandName(const std::string& name)
{
    commandName = name;
}

std::string ParserResult::getCommandName() const
{
    return commandName;
}

void ParserResult::setFilter(const std::string& filter)
{
    this->filter = filter;
}

std::string ParserResult::getFilter() const
{
    return filter;
}

void ParserResult::setFlag(const std::string& flagName)
{
    flags.emplace(flagName);
}

bool ParserResult::getFlag(const std::string& flagName) const
{
    return flags.find(flagName) != flags.end();
}

void ParserResult::setDefaultParameter(const std::string& value)
{
    defaultParameter = value;
}

std::string ParserResult::getDefaultParameter() const
{
    return defaultParameter;
}

void ParserResult::setParameter(const std::string& name, const std::string& value)
{
    arguments[name] = value;
}

std::string ParserResult::getParameter(const std::string& name) const
{
    if (arguments.find(name) == arguments.end())
        return "";

    return arguments.at(name);
}

} // namespace Cli
