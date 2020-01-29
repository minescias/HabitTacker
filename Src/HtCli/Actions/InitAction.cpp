#include "HtCli/Actions/InitAction.h"

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include "HT/Dao/DatabaseCreator.h"
#include "HtCli/Actions/ActionError.h"

namespace Actions
{
using json = nlohmann::json;
namespace fs = std::filesystem;

InitAction::InitAction() : configFilename("htr_settings.json")
{
}

void InitAction::execute(const std::string& dbFilePath)
{
	dbFilename = dbFilePath;

	createDatabaseFile();
	createConfigFile();
}

void InitAction::createDatabaseFile() const
{
	if (dbFilename.empty())
		throw ActionError("No filename specified");

	if (fs::exists(dbFilename))
		throw ActionError(std::string("File ") + dbFilename + " already exists");

	Dao::DatabaseCreator(dbFilename).createEmptyDatabase();
}

void InitAction::createConfigFile() const
{
	if (configFilename.empty())
		throw ActionError("Config file path is empty");

	auto configFilePath =
		fs::path(dbFilename).parent_path().append(configFilename);

	std::ofstream file{configFilePath};
	file << json{{"database", dbFilename}}.dump(4);
	file.close();
}

} // namespace Actions
