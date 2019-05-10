#ifndef __COMMAND_LINE_PARSER_H
#define __COMMAND_LINE_PARSER_H

#include <string>
#include <vector>

#include "HT/Cli/ParserResult.h"

namespace Cli
{

class CommandLineParser
{
public:
    CommandLineParser();
    ParserResult parse(int argc, char** argv);

    std::string getCommandName() const;
    std::string getArguments() const;
    std::string getFilter() const;

private:
    std::string commandName;
    std::string arguments;
    std::string filter;
};

} // namespace Cli

#endif
