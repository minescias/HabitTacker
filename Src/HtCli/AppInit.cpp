#include "HtCli/AppInit.h"

#include <filesystem>
#include <iostream>

#include "CLI/App.hpp"
#include "CLI/CLI.hpp"

#include "Core/Config/Settings.h"
#include "Core/Database/Database.h"
#include "Core/Logger/Log.h"
#include "Core/Logger/LogConfig.h"
#include "Core/Logger/Logger.h"

#include "HtCli/AppInit/GetSettings.h"
#include "HtCli/AppInit/InitDaoFactory.h"
#include "HtCli/AppInit/RegisterCommands.h"
#include "HtCli/AppInit/Vesrion.h"
#include "HtCli/Commands/CommandError.h"

auto openDatabase(const std::string& filename)
{
	if (std::filesystem::exists(filename))
		return Db::Database(filename);
	else
		throw Commands::CommandError("Missing database file in " + filename);
}

auto initLogger()
{
	auto logConfig = std::make_unique<Log::Config>();
	logConfig->enabled = false;
	logConfig->levels = {Log::Levels::Error, Log::Levels::Sql, Log::Levels::Common};
	auto logger = std::make_unique<Log::Logger>(std::move(logConfig));
	Log::setLogger(logger.get());

	return logger;
}

int appInit(int argc, char* argv[])
{
	auto logger = initLogger();

	CLI::App app;

	auto versionFlag = app.add_flag("-v,--version", "Prints program version");
	auto commands = registerCommands(&app);

	CLI11_PARSE(app, argc, argv);

	if (versionFlag->count())
	{
		printVersionNumber();
		return 0;
	}

	if (app.get_subcommand("init")->count() == 1)
		commands->get("init")->execute();

	for (auto& [name, command] : commands->getAllCommands())
	{
		if (app.get_subcommand(name)->count() == 1)
		{
			auto settings = getSettings();
			log("Opening database file " + settings->get("database"));
			auto database = openDatabase(settings->get("database"));
			auto daoFactory = AppInit::initDaoFactory(&database);

			command->setDaoFactory(daoFactory.get());

			try
			{
				command->execute();
			}
			catch (const Commands::CommandError& err)
			{
				std::cout << err.what() << "\n";
			}
			catch (const RuntimeError& err)
			{
				std::cout << err.what() << "\n";
			}
		}
	}

	return 0;
}
