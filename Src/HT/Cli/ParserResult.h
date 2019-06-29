#ifndef __PARSER_RESULT_H
#define __PARSER_RESULT_H

#include <map>
#include <set>
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

	void setFilter(const std::string& filter);
	std::string getFilter() const;

	void setFlag(const std::string& flagName);
	bool getFlag(const std::string& flagName) const;

	std::set<std::string> flags;
	std::string commandName;
	std::string filter;
	Arguments arguments;
};

} // namespace Cli

#endif
