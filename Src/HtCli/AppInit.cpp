#include "HtCli/AppInit.h"

#include <iostream>

#include <Core/Cli/CommandLineParser.h>
#include <Core/Config/Settings.h>
#include <Core/Database/Database.h>
#include <Core/Logger/Log.h>
#include <Core/Logger/Logger.h>

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/InitAction.h"

#include "HtCli/AppInit/GetSettings.h"
#include "HtCli/AppInit/Help.h"
#include "HtCli/AppInit/InitDaoFactory.h"
#include "HtCli/AppInit/RegisterActions.h"
#include "HtCli/AppInit/Vesrion.h"

int appInit(int argc, char* argv[])
{
    Cli::CommandLineParser parser;
    auto parserResult = Cli::CommandLineParser().parse(argc, argv);
    auto commandName = parserResult.getCommandName();

    auto logConfig = std::make_unique<Log::Config>();
    logConfig->enabled = true;
    logConfig->levels = {Log::Levels::Error, Log::Levels::Sql};
    auto logger = std::make_unique<Log::Logger>(std::move(logConfig));
    Log::setLogger(logger.get());

    log ("Execute command: " + commandName);

    if (commandName == "help")
    {
        printHelpMessage();
        return 0;
    }

    if (commandName == "version")
    {
        printVersionNumber();
        return 0;
    }

    try
    {
        if (commandName == "init")
        {
            Actions::InitAction().execute(
                parserResult.getDefaultParameter(), "htr.ini");

            return 0;
        }


        auto settings = getSettings("htr.ini");
        auto database = Db::Database(settings->get("database"));
        auto daoFactory = AppInit::initDaoFactory(&database);
        auto actionRegister = registerActions();
        auto action = actionRegister->get(commandName);

        action->setDaoFactory(daoFactory.get());
        action->execute(parserResult);
    }
    catch (const Actions::ActionError& err)
    {
        std::cout << err.what() << "\n";
    }
    catch (const RuntimeError& err)
    {
        std::cout << err.what() << "\n";
    }

    return 0;
}
