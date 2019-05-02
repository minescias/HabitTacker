#include "HT/CommandLineParser.h"

#include <algorithm>
#include <cctype>

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
{
}

void CommandLineParser::parse(int argc, char** argv)
{
	// ależ to jest straszne
	for (int i=1; i< argc; i++)
	{
		if ( i==1 && is_number(argv[i]))
			filter = argv[i];
		else if (commandName.empty())
			commandName = argv[i];
		else if (arguments.empty())
			arguments = argv[i];
	}
}

std::string CommandLineParser::getCommandName() const
{
	return commandName;
}

std::string CommandLineParser::getArguments() const
{
	return arguments;
}

std::string CommandLineParser::getFilter() const
{
	return filter;
}

} // namespace Cli
