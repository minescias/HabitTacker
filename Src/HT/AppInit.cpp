#include "HT/AppInit.h"

#include <iostream>

#include "HT/Actions/InitAction.h"
#include "HT/CommandLineParser.h"
#include "HT/Actions/HelpAction.h"

int appInit(int argc, char* argv[])
{
    CommandLineParser parser;
    parser.parse(argc, argv);

    if (parser.getCommandName() == "init")
        Actions::InitAction().execute();
    else if (parser.getCommandName() == "help")
        Actions::HelpAction().execute();
    else
        std::cout << "Unknown command\n";

    return 0;
}
