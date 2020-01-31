#include "HtCli/AppInit.h"

#include <iostream>

#include <Core/Cli/CommandLineParser.h>
#include <Core/Config/Settings.h>
#include <Core/Database/Database.h>
#include <Core/Logger/Log.h>
#include <Core/Logger/Logger.h>

#include "Core/Logger/LogConfig.h"
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
	logConfig->enabled = false;
	logConfig->levels = {Log::Levels::Error, Log::Levels::Sql, Log::Levels::Common};
	auto logger = std::make_unique<Log::Logger>(std::move(logConfig));
	Log::setLogger(logger.get());

	try
	{
		if (commandName == "help")
		{
			printHelpMessage();
		}
		else if (commandName == "version")
		{
			printVersionNumber();
		}
		else if (commandName == "init")
		{
			Actions::InitAction().execute(parserResult);
		}
		else
		{
			auto settings = getSettings();
			log("Opening database file " + settings->get("database"));
			auto database = Db::Database(settings->get("database"));
			auto daoFactory = AppInit::initDaoFactory(&database);
			auto actionRegister = registerActions();
			auto action = actionRegister->get(commandName);

			action->setDaoFactory(daoFactory.get());
			action->execute(parserResult);
		}
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
