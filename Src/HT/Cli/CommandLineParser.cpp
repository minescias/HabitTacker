#include "HT/Cli/CommandLineParser.h"

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

ParserResult CommandLineParser::parse(int argc, char** argv)
{
	ParserResult result;

	for (int i=1; i< argc; i++)
	{
		if ( i==1 && is_number(argv[i]))
			result.filter = argv[i];
		else if (result.commandName.empty())
			result.commandName = argv[i];
		else if (result.argument.empty())
			result.argument = argv[i];
	}

	return result;
}

} // namespace Cli
