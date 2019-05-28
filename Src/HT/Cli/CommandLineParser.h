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
};

} // namespace Cli

#endif
