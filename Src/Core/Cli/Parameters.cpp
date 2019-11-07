#include "Core/Cli/Parameters.h"

namespace Cli
{
Parameters::Parameters()
{
}

void Parameters::setCommandName(const std::string& name)
{
	commandName = name;
}

std::string Parameters::getCommandName() const
{
	return commandName;
}

void Parameters::setFilter(const std::string& filter)
{
	this->filter = filter;
}

std::string Parameters::getFilter() const
{
	return filter;
}

void Parameters::setFlag(const std::string& flagName)
{
	arguments[flagName] = "";
}

bool Parameters::getFlag(const std::string& flagName) const
{
	return arguments.find(flagName) != arguments.end()
		&& arguments.at(flagName).empty();
}

void Parameters::setDefaultParameter(const std::string& value)
{
	defaultParameter = value;
}

std::string Parameters::getDefaultParameter() const
{
	return defaultParameter;
}

void Parameters::setParameter(const std::string& name, const std::string& value)
{
	arguments[name] = value;
}

std::string Parameters::getParameter(const std::string& name) const
{
	if (arguments.find(name) == arguments.end())
		return "";

	return arguments.at(name);
}

std::map<std::string, std::string> Parameters::getAllArguments() const
{
	return arguments;
}

} // namespace Cli
