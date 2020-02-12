#include "HtCli/Actions/InitAction.h"

#include <filesystem>
#include <fstream>

#include <pwd.h>
#include <unistd.h>

#include "CLI/CLI.hpp"
#include "fmt/format.h"
#include "nlohmann/json.hpp"

#include "Core/Cli/ValidatorEnums.h"
#include "HT/Dao/DatabaseCreator.h"
#include "HtCli/Actions/ActionError.h"

namespace Actions
{
using json = nlohmann::json;
namespace fs = std::filesystem;

InitAction::InitAction() : configFileName("htr_settings.json")
{
}

void InitAction::execute()
{
	createDatabaseFile();
	createConfigFile();
}

void InitAction::addCliOptions(CLI::App* app)
{
	auto command =
		app->add_subcommand("init", "Creates new database and config file");
	command->add_option("-f,--filename", dbFilename, "Database file name")->required();
	command->add_flag(
		"-g,--global", global, "Create config file in home directory");
}

void InitAction::createDatabaseFile() const
{
	if (fs::exists(dbFilename))
		throw ActionError(fmt::format("File {} already exists", dbFilename));

	Dao::DatabaseCreator(dbFilename).createEmptyDatabase();
}

void InitAction::createConfigFile() const
{
	auto configFilePath = fs::path();

	if (global)
	{
		// https://stackoverflow.com/questions/2910377/get-home-directory-in-linux
		auto homeDir = getenv("HOME");
		if (!homeDir)
			homeDir = getpwuid(getuid())->pw_dir;

		configFilePath = fs::path(homeDir).append(".config/htr/");
	}
	else
	{
		configFilePath = fs::path(dbFilename).parent_path();
	}

	if (!configFilePath.empty())
		fs::create_directory(configFilePath);

	configFilePath.append(configFileName);
	std::ofstream file{configFilePath};

	if (!file.is_open())
	{
		throw ActionError(
			std::string("Cannot create config file in ") + configFilePath.c_str());
	}

	file << json{{"database", fs::current_path().append(dbFilename)}}.dump(4);
	file.close();
}

} // namespace Actions
