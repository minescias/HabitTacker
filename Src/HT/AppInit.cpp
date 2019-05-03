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
#include "HT/CommandLineParser.h"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/HabitDao.h"

void executeAddAction(const std::string& addName);
void executeListAction();
void executeDoneAction(const std::string& filter);
void executeDefaultAction();

void printVersion();

int appInit(int argc, char* argv[])
{
	try
	{
		Cli::CommandLineParser parser;
		parser.parse(argc, argv);

		auto command = parser.getCommandName();

		if (command == "")
			executeDefaultAction();
		else if (command == "init")
			Actions::InitAction().execute(parser.getArguments());
		else if (command == "add")
			executeAddAction(parser.getArguments());
		else if (command == "done")
			executeDoneAction(parser.getFilter());
		else if (command == "list")
			executeListAction();
		else if (command == "help")
			Actions::HelpAction().execute();
		else if (command == "version")
			printVersion();
		else
			std::cout << "Unknown command\n";
	}
	catch(const ActionError& err)
	{
		std::cout << err.what() << "\n";
	}

	return 0;
}

void executeAddAction(const std::string& habitName)
{
	// I'll add some way to pass database name later
	auto database = Db::Database("Test.db");
	auto hdDao = Dao::HabitDefinitionDao(&database);

	Actions::AddAction(&hdDao).execute(habitName);
}

void executeListAction()
{
	// I'll add some way to pass database name later
	auto database = Db::Database("Test.db");
	auto hdDao = Dao::HabitDefinitionDao(&database);

	Actions::ListAction(&hdDao).execute();
}

void executeDoneAction(const std::string& filter)
{
	// I'll add some way to pass database name later
	auto database = Db::Database("Test.db");
	auto definitionDao = Dao::HabitDefinitionDao(&database);
	auto habitDao = Dao::HabitDao(&database);
	Actions::DoneAction(&habitDao, &definitionDao).execute(filter);
}

void executeDefaultAction()
{
	auto today = time(nullptr);
	auto secondsInDay{86400};	// 86400 = 24 * 60 * 60
	today -= (today % secondsInDay);

	// I'll add some way to pass database name later
	auto database = Db::Database("Test.db");
	auto definitionDao = Dao::HabitDefinitionDao(&database);
	auto habitDao = Dao::HabitDao(&database);
	Actions::DefaultAction(&habitDao, &definitionDao).execute(today);
}

void printVersion()
{
	std::cout << "Habit Tracker V0.1\n";
}