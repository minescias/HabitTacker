#include "HT/Cli/CommandLineParser.h"

#include <algorithm>
#include <cctype>

#include <Core/Utils/Exceptions/RuntimeError.h>

namespace
{

// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c :)
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

} // namespace

namespace Cli
{

CommandLineParser::CommandLineParser()
	: commandIsSet(false)
{
	result.arguments = Arguments{{"", ""}};
}

ParserResult CommandLineParser::parse(int argc, char** argv)
{
	for (int i=1; i< argc; i++)
	{
		if ( i==1 && is_number(argv[i]))
		{
			result.filter = argv[i];
		}
		else
		{
			auto parameterType = getParameterType(argv[i]);

			if (parameterType == ParameterType::Simple)
				readSimpleParameter(argv[i]);
			else if (parameterType == ParameterType::Flag)
				readFlag(argv[i]);
			else if (parameterType == ParameterType::Parameter)
				readParameter(argv[i]);
		}
	}

	return result;
}

ParameterType CommandLineParser::getParameterType(const std::string& parameter) const
{
	if (*parameter.begin() == '-')
	{
		if (parameter.find('=') != std::string::npos)
			return ParameterType::Parameter;
		else
			return ParameterType::Flag;
	}

	return ParameterType::Simple;
}

void CommandLineParser::readSimpleParameter(const std::string& parameter)
{
	if (result.commandName.empty())
	{
		result.commandName = parameter;
		return;
	}

	if (!result.arguments.at("").empty())
		throw RuntimeError("Unknown command '" + parameter + "'");

	result.arguments[""] = parameter;
}

void CommandLineParser::readFlag(const std::string& parameter)
{
	auto flag = parameter.substr(1);

	if (result.arguments.find(flag) != result.arguments.end())
		throw RuntimeError("Redefinition of '" + flag + "' parameter");

	result.arguments[flag] = "";
}

void CommandLineParser::readParameter(const std::string& parameter)
{
	auto equalPos = parameter.find('=');
	auto param = parameter.substr(1, equalPos - 1);
	auto value = parameter.substr(equalPos + 1);

	result.arguments[param] = value;
}

} // namespace Cli
