#include <gmock/gmock.h>

#include <filesystem>
#include <fstream>

#include "Core/Config/Settings.h"
#include "Core/Config/ConfigFile.h"
#include "Core/Utils/Exceptions/RuntimeError.h"

namespace
{

auto filename = "tests/configFile.txt";

} // namespace

namespace Tests
{

using namespace testing;

class ConfigFileTests : public testing::Test
{
public:
	ConfigFileTests(){};

	void createConfigFile(const std::string& content)
	{
		// https://stackoverflow.com/questions/36775493/create-file-with-filesystem-c-library
		std::filesystem::path path{filename};
		std::filesystem::create_directories(path.parent_path());

		std::ofstream ofs(path);
		ofs << content;
		ofs.close();
	}
};

TEST_F(ConfigFileTests, readsSettingsFromFile)
{
	auto name = "database";

	auto configFileContent =
		"# default database file\n"
		"database=myDatabase.db\n";

	createConfigFile(configFileContent);

	auto expectedSettings = std::make_unique<Config::Settings>();
	expectedSettings->registerSettings({{name, "myDatabase.db"}});

	auto settings = std::make_unique<Config::Settings>();
	settings->registerSettings({{name, ""}});

	Config::ConfigFile(filename, settings.get()).read();

	ASSERT_STREQ(expectedSettings->get(name).c_str(), settings->get(name).c_str());
}

TEST_F(ConfigFileTests, throwsRuntimeErrorWhenNoEqFund)
{
	auto configFileContent ="slskjjhsfkjhskjf\n";
	createConfigFile(configFileContent);

	auto settings = std::make_unique<Config::Settings>();

	try
	{
		Config::ConfigFile(filename, settings.get()).read();
		FAIL() << "RuntimeError expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Error in config file in line 'slskjjhsfkjhskjf'";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
