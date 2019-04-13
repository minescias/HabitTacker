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
    std::vector<std::string> getArguments() const;

private:
    std::string commandName;
    std::vector<std::string> arguments;
};

#endif
