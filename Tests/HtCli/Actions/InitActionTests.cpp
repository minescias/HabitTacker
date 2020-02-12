#include <gmock/gmock.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "CLI/App.hpp"
#include "CLI/Error.hpp"
#include "nlohmann/json.hpp"

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/InitAction.h"

namespace
{
using namespace testing;
using json = nlohmann::json;
namespace fs = std::filesystem;

void parseArguments(CLI::App* app, std::vector<std::string> arguments)
{
	std::reverse(arguments.begin(), arguments.end());
	app->parse(arguments);
}

} // namespace

namespace Tests
{
class InitActionTest : public testing::Test
{
public:
	InitActionTest()
		: dbFilePath("test_files/HtCli_InitAction.db"),
		  configFilePath("test_files/htr_settings.json")
	{
		fs::remove(dbFilePath);
		fs::remove(configFilePath);

		initAction.addCliOptions(&app);
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
	Actions::InitAction initAction;
	CLI::App app;
};

TEST_F(InitActionTest, valid_filename_is_set)
{
	try
	{
		parseArguments(&app, {"init"});
		FAIL() << "ParseError expected";
	}
	catch (const CLI::ParseError& err)
	{
		ASSERT_STREQ("--filename is required", err.what());
	}
}

TEST_F(InitActionTest, creates_new_file_when_does_not_exist)
{
	parseArguments(&app, {"init", "--filename", dbFilePath});
	initAction.execute();
	ASSERT_TRUE(fs::exists(dbFilePath));
}

TEST_F(InitActionTest, throwsErrorWhenFileAlreadyExists)
{
	try
	{
		parseArguments(&app, {"init", "--filename", dbFilePath});
		initAction.execute();
		// files already created in prevoius command
		initAction.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const Actions::ActionError& err)
	{
		std::string msg = std::string("File ") + dbFilePath + " already exists";
		ASSERT_STREQ(msg.c_str(), err.what());
	}
}

TEST_F(InitActionTest, createsConfgigFile)
{
	auto filePath = fs::current_path().append("test_files/HtCli_InitAction.db");
	auto fileContent = json{{"database", filePath.c_str()}}.dump(4);

	parseArguments(&app, {"init", "--filename", dbFilePath});
	initAction.execute();
	validateFileContent(configFilePath, fileContent);
}

} // namespace Tests
