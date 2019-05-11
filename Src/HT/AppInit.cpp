#include "HT/AppInit.h"

#include <iostream>

#include <Core/Database/Database.h>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/AddAction.h"
#include "HT/Actions/DefaultAction.h"
#include "HT/Actions/DoneAction.h"
#include "HT/Actions/HelpAction.h"
#include "HT/Actions/InitAction.h"
#include "HT/Actions/ListAction.h"
#include "HT/AppInit/Vesrion.h"
#include "HT/Cli/CommandLineParser.h"
#include "HT/AppInit/DaoFactoryInitializer.h"

template <typename T>
void executeAction(Dao::DaoFactory* factory, Cli::ParserResult pr)
{
	auto action = T();
	action.setDaoFactory(factory);
	action.execute(pr);
}

int appInit(int argc, char* argv[])
{
	Cli::CommandLineParser parser;
	auto parserResult = Cli::CommandLineParser().parse(argc, argv);
	auto command = parserResult.commandName;

	// simple commands
	if (command == "help")
	{
		Actions::HelpAction().execute();
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
			Actions::InitAction().execute(parser.getArguments());
			return 0;
		}

		// I'll add some way to pass database name later
		auto database = Db::Database("Test.db");
		auto daoFactory = initDaoFactory(&database);

		if (command == "")
			executeAction<Actions::DefaultAction>(daoFactory.get(), parserResult);
		else if (command == "init")
			Actions::InitAction().execute(parser.getArguments());
		else if (command == "add")
			executeAction<Actions::AddAction>(daoFactory.get(), parserResult);
		else if (command == "done")
			executeAction<Actions::DoneAction>(daoFactory.get(), parserResult);
		else if (command == "list")
			executeAction<Actions::ListAction>(daoFactory.get(), parserResult);
		else
			std::cout << "Unknown command\n";
	}
	catch(const ActionError& err)
	{
		std::cout << err.what() << "\n";
	}

	return 0;
}
