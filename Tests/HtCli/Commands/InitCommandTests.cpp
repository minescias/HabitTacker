#include <gmock/gmock.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "CLI/App.hpp"
#include "CLI/Error.hpp"
#include "nlohmann/json.hpp"

#include "HtCli/Commands/CommandError.h"
#include "HtCli/Commands/InitCommand.h"

#include "Tests/HtCli/Tools/CliTestTools.h"

namespace
{
using namespace testing;
using json = nlohmann::json;
namespace fs = std::filesystem;

} // namespace

namespace Tests
{
class InitCommandTests : public testing::Test
{
public:
	InitCommandTests()
		: dbFilePath("test_files/HtCli_InitAction.db"),
		  configFilePath("test_files/htr_settings.json")
	{
		fs::remove(dbFilePath);
		fs::remove(configFilePath);

		initCommand.setCliParameters(&app);
	}

	void validateFileContent(const std::string& filename, const std::string& expectedContent)
	{
		std::ifstream file(filename);
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		ASSERT_STREQ(ss.str().c_str(), expectedContent.c_str());
	}

	std::string dbFilePath;
	std::string configFilePath;
	Commands::InitCommand initCommand;
	CLI::App app;
};

TEST_F(InitCommandTests, valid_filename_is_set)
{
	parseAndThrowError(&app, {"init"}, "--filename is required");
}

TEST_F(InitCommandTests, creates_new_file_when_does_not_exist)
{
	parseArguments(&app, {"init", "--filename", dbFilePath});
	initCommand.execute();
	ASSERT_TRUE(fs::exists(dbFilePath));
}

TEST_F(InitCommandTests, throwsErrorWhenFileAlreadyExists)
{
	try
	{
		parseArguments(&app, {"init", "--filename", dbFilePath});
		initCommand.execute();
		// files already created in prevoius command
		initCommand.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const Commands::CommandError& err)
	{
		std::string msg = std::string("File ") + dbFilePath + " already exists";
		ASSERT_STREQ(msg.c_str(), err.what());
	}
}

// TEST_F(InitCommandTests, createsConfgigFile)
// {
// 	auto filePath = fs::current_path().append("test_files/HtCli_InitAction.db");
// 	auto fileContent = json{{"database", filePath.c_str()}}.dump(4);

// 	parseArguments(&app, {"init", "--filename", dbFilePath});
// 	initAction.execute();
// 	validateFileContent(configFilePath, fileContent);
// }

} // namespace Tests
