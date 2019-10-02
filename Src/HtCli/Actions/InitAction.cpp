#include "HtCli/Actions/InitAction.h"

#include <filesystem>
#include <fstream>

#include "HtCli/Actions/ActionError.h"
#include "HT/Dao/DatabaseCreator.h"

namespace Actions
{

InitAction::InitAction()
{
}

void InitAction::execute(const std::string& dbFilePath,
	const std::string& configFilePath)
{
	dbFilename = dbFilePath;
	configFilename = configFilePath;

	createDatabaseFile();
	createConfigFile();
}

void InitAction::createDatabaseFile() const
{
	if (dbFilename.empty())
		throw ActionError("No filename specified");

	if (std::filesystem::exists(dbFilename))
		throw ActionError(std::string("File ") + dbFilename + " already exists");

	Dao::DatabaseCreator(dbFilename).createEmptyDatabase();
}

void InitAction::createConfigFile() const
{
	if (configFilename.empty())
		throw ActionError("Config file path is empty");

	std::ofstream file{configFilename};
	file << "# defaultDatabase\n"
		"database=" << dbFilename << "\n";

	file.close();

}

} // namespace Actions
