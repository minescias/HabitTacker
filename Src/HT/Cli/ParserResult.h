#ifndef __PARSER_RESULT_H
#define __PARSER_RESULT_H

#include <string>

namespace Cli
{

struct ParserResult
{
	ParserResult()
	{}

	ParserResult(const std::string& commandName,
		const std::string& filter,
		const std::string& argument)
		: commandName(commandName)
		, filter(filter)
		, argument(argument)
	{}

	std::string commandName;
	std::string filter;
	std::string argument;
};

} // namespace Cli

#endif
