#include <gmock/gmock.h>

#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

#include "Core/Config/ConfigFile.h"
#include "Core/Config/Settings.h"
#include "Core/Exceptions/RuntimeError.h"

namespace Tests
{
using namespace testing;
using json = nlohmann::json;

class ConfigFileTests : public testing::Test
{
public:
	ConfigFileTests() : filename("test_files/Core_ConfigFile.txt"){};

	void createConfigFile(const std::string& content)
	{
		// https://stackoverflow.com/questions/36775493/create-file-with-filesystem-c-library
		// std::filesystem::path path{filename};
		std::ofstream ofs(filename);
		ofs << content;
		ofs.close();
	}

	std::string filename;
};

TEST_F(ConfigFileTests, readsSettingsFromFile)
{
	auto name = "database";
	auto configFileContent = json{{name, "myDatabase.db"}}.dump(4);
	createConfigFile(configFileContent);

	auto expectedSettings = std::make_unique<Config::Settings>();
	expectedSettings->registerSettings({{name, "myDatabase.db"}});

	auto settings = std::make_unique<Config::Settings>();
	settings->registerSettings({{name, ""}});

	Config::ConfigFile(filename, settings.get()).read();

	ASSERT_THAT(settings->get(name), Eq(expectedSettings->get(name)));
}

} // namespace Tests
