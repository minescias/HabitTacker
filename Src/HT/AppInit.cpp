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
#include "HT/Cli/CommandLineParser.h"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/HabitDao.h"

void executeListAction(Dao::DaoFactory* daoFactory);
void executeDefaultAction(Dao::DaoFactory* daoFactory);

void printVersion();
std::unique_ptr<Dao::DaoFactory> initDaoFactory(Db::Database* db);

template <typename T>
void executeAction(Dao::DaoFactory* factory, Cli::ParserResult pr)
{
	auto action = T();
	action.setDaoFactory(factory);
	action.execute(pr);
}

int appInit(int argc, char* argv[])
{
	try
	{
		Cli::CommandLineParser parser;
		auto parserResult = parser.parse(argc, argv);

		auto command = parserResult.commandName;

		if (command == "init")
		{
			Actions::InitAction().execute(parser.getArguments());
			return 0;
		}

		// I'll add some way to pass database name later
		auto database = Db::Database("Test.db");
		auto daoFactory = initDaoFactory(&database);

		if (command == "")
			executeDefaultAction(daoFactory.get());
		else if (command == "init")
			Actions::InitAction().execute(parser.getArguments());
		else if (command == "add")
			executeAction<Actions::AddAction>(daoFactory.get(), parserResult);
		else if (command == "done")
			executeAction<Actions::DoneAction>(daoFactory.get(), parserResult);
		else if (command == "list")
			executeListAction(daoFactory.get());
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

std::unique_ptr<Dao::DaoFactory> initDaoFactory(Db::Database* db)
{
	auto daoFactory = std::make_unique<Dao::DaoFactory>();
	daoFactory->setDatabase(db);

	daoFactory->registerDao("habitDefinition", [](Db::Database* db){
		return std::make_unique<Dao::HabitDefinitionDao>(db);});

	daoFactory->registerDao("habit", [](Db::Database* db){
		return std::make_unique<Dao::HabitDao>(db);});

	return daoFactory;
}

void executeListAction(Dao::DaoFactory* daoFactory)
{
	auto action = Actions::ListAction();
	action.setDaoFactory(daoFactory);
	action.execute();
}

void executeDefaultAction(Dao::DaoFactory* daoFactory)
{
	auto today = time(nullptr);
	auto secondsInDay{86400};	// 86400 = 24 * 60 * 60
	today -= (today % secondsInDay);

	auto action = Actions::DefaultAction();
	action.setDaoFactory(daoFactory);
	action.execute(today);
}

void printVersion()
{
	std::cout << "Habit Tracker V0.1\n";
}
