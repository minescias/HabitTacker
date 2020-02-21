#include <gmock/gmock.h>

#include "CLI/App.hpp"
#include "Core/Exceptions/RuntimeError.h"

#include "HtCli/Commands/CommandRegister.h"
#include "HtCli/Commands/ICommand.h"

namespace
{
int actionResult = 0;

class FirstAction : public Commands::ICommand
{
public:
	void setDaoFactory(Dao::DaoFactory* daoFactory){};
	void setCliParameters(CLI::App* app)
	{
	}
	void execute()
	{
		actionResult = 1;
	};
};

class SecondAction : public Commands::ICommand
{
public:
	void setDaoFactory(Dao::DaoFactory* daoFactory){};
	void setCliParameters(CLI::App* app)
	{
	}
	void execute()
	{
		actionResult = 2;
	};
};

} // namespace

namespace Tests
{
using namespace testing;

TEST(ActionRegisterTest, registerAndGetActions)
{
	CLI::App app;
	auto commandRegister = Commands::CommandRegister(&app);
	commandRegister.reg("firstAction", std::make_unique<FirstAction>());
	commandRegister.reg("secondAction", std::make_unique<SecondAction>());

	commandRegister.get("firstAction")->execute();
	EXPECT_THAT(actionResult, Eq(1));
	commandRegister.get("secondAction")->execute();
	EXPECT_THAT(actionResult, Eq(2));
}

TEST(ActionRegisterTest, throwsLogicErrorWhenRegisteringTheSameActionTwice)
{
	CLI::App app;
	auto actionRegister = Commands::CommandRegister(&app);
	actionRegister.reg("firstAction", std::make_unique<FirstAction>());

	try
	{
		actionRegister.reg("firstAction", std::make_unique<FirstAction>());
		FAIL() << "LogicError expected";
	}
	catch (LogicError& err)
	{
		auto expected = "Redefinition of 'firstAction' action";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ActionRegisterTest, throwsRuntimeErrorWhenGettingUnregisteredAction)
{
	CLI::App app;
	auto actionRegister = Commands::CommandRegister(&app);
	try
	{
		actionRegister.get("firstAction");
		FAIL() << "LogicError expected";
	}
	catch (RuntimeError& err)
	{
		auto expected = "Action 'firstAction' is not registered";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
