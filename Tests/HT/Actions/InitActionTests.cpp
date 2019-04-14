#include <gmock/gmock.h>

#include <filesystem>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/InitAction.h"

using namespace testing;
namespace fs = std::filesystem;

const char* filename = "test_DgQADg8ICA0.db";

class InitActionTest : public testing::Test
{
public:
	InitActionTest(){}

	Actions::InitAction initAction;
};

TEST_F(InitActionTest, validFilenameIsSet)
{
	try
	{
		initAction.execute("");
		FAIL() << "Expected ActionError";
	}
	catch(const ActionError& err)
	{
		ASSERT_STREQ("No filename specified", err.what());
	}
}

TEST_F(InitActionTest, createsNewFileWhenDoesntExist)
{
	//ensure that file doesn't exist
	fs::remove(filename);

	initAction.execute(filename);
	ASSERT_TRUE(fs::exists(filename));
}

TEST_F(InitActionTest, throwsErrorWhenFileAlreadyExists)
{
	try
	{
		// previous test should ensure that required file exists
		initAction.execute(filename);
		FAIL() << "Expected ActionError";
	}
	catch(const ActionError& err)
	{
		std::string msg = std::string("File ") + filename + " already exists";
		ASSERT_STREQ(msg.c_str(), err.what());
	}
}


