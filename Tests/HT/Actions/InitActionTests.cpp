#include <gmock/gmock.h>

#include <filesystem>
#include <fstream>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/InitAction.h"

namespace
{

using namespace testing;
namespace fs = std::filesystem;

const auto dbFilePath = "tests/test_initAction.db";
const auto configFilePath = "tests/test_initActionConfig.txt";

} // namespace

namespace Tests
{

class InitActionTest : public testing::Test
{
public:
	InitActionTest()
	{
		fs::remove(dbFilePath);
	}

	void validateFileContent(const std::string& filename,
		const std::string& expectedContent)
	{
		std::ifstream file(filename);

		if (!file.is_open())
			FAIL() << std::string("Cannot open file ") + filename;

		std::string line;
		std::string fileContent;

		while (getline(file, line)) {
			fileContent += line + "\n";
		}
		file.close();

		ASSERT_STREQ(fileContent.c_str(), expectedContent.c_str());
	}

	Actions::InitAction initAction;
};

TEST_F(InitActionTest, validFilenameIsSet)
{
	try
	{
		initAction.execute("", "");
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		ASSERT_STREQ("No filename specified", err.what());
	}
}

TEST_F(InitActionTest, createsNewFileWhenDoesntExist)
{
	initAction.execute(dbFilePath, configFilePath);
	ASSERT_TRUE(fs::exists(dbFilePath));
}

TEST_F(InitActionTest, throwsErrorWhenFileAlreadyExists)
{
	initAction.execute(dbFilePath, configFilePath);
	try
	{
		// previous test should ensure that required file exists
		initAction.execute(dbFilePath, configFilePath);
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		std::string msg = std::string("File ") + dbFilePath + " already exists";
		ASSERT_STREQ(msg.c_str(), err.what());
	}
}

TEST_F(InitActionTest, validateConfigFileNameIsSet)
{
	try
	{
		initAction.execute(dbFilePath, "");
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		ASSERT_STREQ("Config file path is empty", err.what());
	}
}

TEST_F(InitActionTest, createsConfgigFile)
{
	auto fileContent = std::string(
		"# defaultDatabase\n"
		"database=") + dbFilePath + "\n";

	initAction.execute(dbFilePath, configFilePath);

	validateFileContent(configFilePath, fileContent);
}

} // namespace Tests
