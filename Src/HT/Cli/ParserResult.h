#ifndef __PARSER_RESULT_H
#define __PARSER_RESULT_H

#include <map>
#include <string>

namespace Cli
{

using Arguments = std::map<std::string, std::string>;

struct ParserResult
{
	ParserResult()
	{}

	ParserResult(const std::string& commandName,
		const std::string& filter,
		const Arguments& arguments)
		: commandName(commandName)
		, filter(filter)
		, arguments(arguments)
	{}
	std::string commandName;
	std::string filter;
	Arguments arguments;
};

} // namespace Cli

#endif
