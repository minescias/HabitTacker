#include "HT/AppInit.h"

#include <iostream>

#include <Core/Config/Settings.h>
#include <Core/Database/Database.h>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/InitAction.h"

#include "HT/AppInit/GetSettings.h"
#include "HT/AppInit/InitDaoFactory.h"
#include "HT/AppInit/Help.h"
#include "HT/AppInit/RegisterActions.h"
#include "HT/AppInit/Vesrion.h"

#include "HT/Cli/CommandLineParser.h"

int appInit(int argc, char* argv[])
{
	Cli::CommandLineParser parser;
	auto parserResult = Cli::CommandLineParser().parse(argc, argv);
	auto command = parserResult.commandName;

	if (command == "help")
	{
		printHelpMessage();
		return 0;
	}

	if (command == "version")
	{
		printVersionNumber();
		return 0;
	}

	try
	{
		if (command == "init")
		{
			Actions::InitAction().execute(
				parserResult.arguments.at(""), "htr.ini");

			return 0;
		}

		auto settings = getSettings("htr.ini");
		auto database = Db::Database(settings->get("database"));
		auto daoFactory = AppInit::initDaoFactory(&database);

		auto actionRegister = registerActions();

		auto action = actionRegister->get(parserResult.commandName);
		action->setDaoFactory(daoFactory.get());
		action->execute(parserResult);
	}
	catch(const Actions::ActionError& err)
	{
		std::cout << err.what() << "\n";
	}
	catch(const RuntimeError& err)
	{
		std::cout << err.what() << "\n";
	}

	return 0;
}
