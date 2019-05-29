#include "HT/AppInit.h"

#include <iostream>

#include <Core/Config/Settings.h>
#include <Core/Database/Database.h>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/InitAction.h"

#include "HT/AppInit/DaoFactoryInitializer.h"
#include "HT/AppInit/GetSettings.h"
#include "HT/AppInit/RegisterActions.h"
#include "HT/AppInit/Help.h"
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
		auto daoFactory = initDaoFactory(&database);

		auto actionRegister = registerActions();

		auto action = actionRegister->get(parserResult.commandName);
		action->setDaoFactory(daoFactory.get());
		action->execute(parserResult);
	}
	catch(const ActionError& err)
	{
		std::cout << err.what() << "\n";
	}

	return 0;
}
