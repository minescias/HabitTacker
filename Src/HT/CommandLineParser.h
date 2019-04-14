#ifndef __COMMAND_LINE_PARSER_H
#define __COMMAND_LINE_PARSER_H

#include <string>
#include <vector>

class CommandLineParser
{
public:
    CommandLineParser();
    void parse(int argc, char** argv);

    std::string getCommandName() const;
    std::string getArguments() const;

private:
    std::string commandName;
    std::string arguments;
};

#endif
