#ifndef __COMMAND_LINE_PARSER_H
#define __COMMAND_LINE_PARSER_H

#include <string>
#include <vector>

#include "Core/Cli/Parameters.h"

namespace Cli
{

enum class ParameterType
{
	Simple,
	Flag,
	Parameter,
};

class CommandLineParser
{
public:
	CommandLineParser();
	Parameters parse(int argc, char** argv);

private:
	ParameterType getParameterType(const std::string& parameter) const;
	void readSimpleParameter(const std::string& parameter);
	void readFlag(const std::string& parameter);
	void readParameter(const std::string& parameter);

private:
	bool commandIsSet;
	Parameters result;
};

} // namespace Cli

#endif
