#include "HT/AppInit.h"

#include <iostream>

#include "HT/Actions/InitAction.h"
#include "HT/CommandLineParser.h"

int appInit(int argc, char* argv[])
{
    CommandLineParser parser;
    parser.parse(argc, argv);

    if (parser.getCommandName() == "init")
        Actions::InitAction().execute();
    else
        std::cout << "Unknown command\n";

    return 0;
}
