#include "HtCli/Commands/InitCommand.h"

#include <filesystem>
#include <fstream>
#include <pwd.h>
#include <unistd.h>

#include "CLI/CLI.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "nlohmann/json.hpp"

#include "Core/Cli/ValidatorEnums.h"

#include "HT/Dao/DatabaseCreator.h"
#include "HtCli/Commands/CommandError.h"

namespace Commands
{
using json = nlohmann::json;
namespace fs = std::filesystem;

InitCommand::InitCommand() : configFileName("htr_settings.json")
{
}

void InitCommand::execute()
{
	createDatabaseFile();
	createConfigFile();
}

void InitCommand::setCliParameters(CLI::App* app)
{
	auto command =
		app->add_subcommand("init", "Creates new database and config file");
	command->add_option("-f,--filename", dbFilename, "Database file name")->required();
	command->add_flag(
		"-g,--global", global, "Create config file in home directory");
}

void InitCommand::setDaoFactory(Dao::DaoFactory* daoFactory)
{
}

void InitCommand::createDatabaseFile() const
{
	if (fs::exists(dbFilename))
		throw CommandError(fmt::format("File {} already exists", dbFilename));

	Dao::DatabaseCreator(dbFilename).createEmptyDatabase();
}

void InitCommand::createConfigFile() const
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
		throw CommandError(
			fmt::format("Cannot create config file in %1%", configFilePath.c_str()));
	}

	file << json{{"database", fs::current_path().append(dbFilename)}}.dump(4);
	file.close();
}

} // namespace Commands
