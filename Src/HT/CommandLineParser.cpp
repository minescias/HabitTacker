#include "HT/CommandLineParser.h"

CommandLineParser::CommandLineParser()
{
}

void CommandLineParser::parse(int argc, char** argv)
{
	if (argc > 1)
		commandName = argv[1];

	if (argc > 2)
		arguments.push_back(argv[2]);

	// for (int i=2; i<argc; i++)
	// 	arguments.emplace_back(argv[i]);
}

std::string CommandLineParser::getCommandName() const
{
	return commandName;
}

std::vector<std::string> CommandLineParser::getArguments() const
{
	return arguments;
}
