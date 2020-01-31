#include <gmock/gmock.h>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "nlohmann/json.hpp"

#include "Core/Cli/Parameters.h"
#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/InitAction.h"

namespace
{
using namespace testing;
using json = nlohmann::json;
namespace fs = std::filesystem;

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

		parameters.setDefaultParameter(dbFilePath);
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
	Cli::Parameters parameters;
};

TEST_F(InitActionTest, validFilenameIsSet)
{
	try
	{
		initAction.execute(Cli::Parameters());
		FAIL() << "Expected RuntimeError";
	}
	catch (const RuntimeError& err)
	{
		ASSERT_STREQ("No filename specified", err.what());
	}
}

TEST_F(InitActionTest, createsNewFileWhenDoesntExist)
{
	initAction.execute(parameters);
	ASSERT_TRUE(fs::exists(dbFilePath));
}

TEST_F(InitActionTest, throwsErrorWhenFileAlreadyExists)
{
	try
	{
		initAction.execute(parameters);
		// files already created in prevoius command
		initAction.execute(parameters);
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
	auto filePath =
		fs::current_path().append("test_files/HtCli_InitAction.db").c_str();

	auto fileContent = json{{"database", filePath}}.dump(4);

	initAction.execute(parameters);
	validateFileContent(configFilePath, fileContent);
}

} // namespace Tests
