#ifndef __COMMAND_LINE_PARSER_H
#define __COMMAND_LINE_PARSER_H

#include <string>
#include <vector>

#include "HT/Cli/ParserResult.h"

namespace Cli
{

enum class ParameterType
{
	Simple,
	Flag,
};

class CommandLineParser
{
public:
	CommandLineParser();
	ParserResult parse(int argc, char** argv);

private:
	ParameterType getParameterType(const std::string& parameter) const;
	void readSimpleParameter(const std::string& parameter);
	void readFlag(const std::string& parameter);
private:
	bool commandIsSet;
	ParserResult result;
};

} // namespace Cli

#endif
