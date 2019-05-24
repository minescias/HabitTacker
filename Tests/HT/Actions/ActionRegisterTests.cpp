#include <gmock/gmock.h>

#include "HT/Actions/ActionRegister.h"
#include "HT/Actions/IAction.h"

namespace
{

int actionResult = 0;

class FirstAction : public Actions::IAction
{
public:
	void setDaoFactory(Dao::DaoFactory* daoFactory){};
	void execute(const Cli::ParserResult& parserResult){actionResult = 1;};
};

class SecondAction : public Actions::IAction
{
public:
	void setDaoFactory(Dao::DaoFactory* daoFactory){};
	void execute(const Cli::ParserResult& parserResult){actionResult = 2;};
};

} // namespace

namespace Tests
{

using namespace testing;

TEST(ActionRegisterTest, registerAndGetActions)
{
	auto actionRegister = Actions::ActionRegister();
	actionRegister.reg("firstAction", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<FirstAction>();});
	actionRegister.reg("secondAction", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<SecondAction>();});

	actionRegister.get("firstAction")->execute(Cli::ParserResult());
	EXPECT_THAT(actionResult, Eq(1));
	actionRegister.get("secondAction")->execute(Cli::ParserResult());
	EXPECT_THAT(actionResult, Eq(2));
}

TEST(ActionRegisterTest, throwsLogicErrorWhenRegisteringTheSameActionTwice)
{
	auto actionRegister = Actions::ActionRegister();
	actionRegister.reg("firstAction", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<FirstAction>();});

	try
	{
		actionRegister.reg("firstAction", []()->std::unique_ptr<Actions::IAction>
			{return std::make_unique<FirstAction>();});
		FAIL() << "LogicError expected";
	}
	catch(LogicError& err)
	{
		auto expected = "Redefinition of 'firstAction' action";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ActionRegisterTest, throwsLogicErrorWhenGettingUnregisteredAction)
{
	auto actionRegister = Actions::ActionRegister();
	try
	{
		actionRegister.get("firstAction");
		FAIL() << "LogicError expected";
	}
	catch(LogicError& err)
	{
		auto expected = "Action 'firstAction' is not registered";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests