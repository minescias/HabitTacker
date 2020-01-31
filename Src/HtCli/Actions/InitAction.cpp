#include "HtCli/Actions/InitAction.h"

#include <filesystem>
#include <fstream>

#include <pwd.h>
#include <nlohmann/json.hpp>
#include <unistd.h>

#include "fmt/format.h"

#include "Core/Cli/ValidatorEnums.h"
#include "HT/Dao/DatabaseCreator.h"
#include "HtCli/Actions/ActionError.h"

namespace Actions
{
using json = nlohmann::json;
namespace fs = std::filesystem;

InitAction::InitAction() : configFileName("htr_settings.json")
{
	initValidator();
}

void InitAction::execute(const Cli::Parameters& parameters)
{
	dbFilename = parameters.getDefaultParameter();

	validator.validate(parameters);
	createDatabaseFile();
	createConfigFile(parameters.getFlag("global"));
}

void InitAction::initValidator()
{
	validator.addDefaultParameter()
		.requirement(Cli::RequirementLevel::Required)
		.errorMessage("No filename specified");

	validator.addParam("global"); // no unit test for this
}

void InitAction::createDatabaseFile() const
{
	if (fs::exists(dbFilename))
		throw ActionError(fmt::format("File {} already exists", dbFilename));

	Dao::DatabaseCreator(dbFilename).createEmptyDatabase();
}

void InitAction::createConfigFile(bool globallyAccesible) const
{
	auto configFilePath = fs::path();

	if (globallyAccesible)
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

	fs::create_directory(configFilePath);
	configFilePath.append(configFileName);

	std::ofstream file{configFilePath};

	if (!file.is_open())
		throw ActionError(std::string("Cannot create config file in ") + configFilePath.c_str());

	file << json{{"database", fs::current_path().append(dbFilename)}}.dump(4);
	file.close();
}

} // namespace Actions
