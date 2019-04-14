#include "HT/AppInit.h"

#include <iostream>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/HelpAction.h"
#include "HT/Actions/InitAction.h"
#include "HT/CommandLineParser.h"

int appInit(int argc, char* argv[])
{

    try
    {
        CommandLineParser parser;
        parser.parse(argc, argv);

        if (parser.getCommandName() == "init")
            Actions::InitAction().execute(parser.getArguments());
        else if (parser.getCommandName() == "help")
            Actions::HelpAction().execute();
        else
            std::cout << "Unknown command\n";
    }
    catch(const ActionError& err)
    {
        std::cout << err.what() << "\n";
    }

    return 0;
}
