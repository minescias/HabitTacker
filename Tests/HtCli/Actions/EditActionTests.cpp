#include <gmock/gmock.h>

#include "CLI/App.hpp"
#include "CLI/Error.hpp"
#include "Core/Cli/Parameters.h"
#include "Core/Dao/DaoFactory.h"
#include "Core/DateTime/ParseDate.h"

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/EditAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/HtCli/Tools/CliTestTools.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{
using namespace testing;

MATCHER_P(DefinitionsAreEqual, expected, "Nie wiem co to za tekst")
{
	EXPECT_THAT(arg.getId(), Eq(expected.getId()));
	EXPECT_THAT(arg.getName(), Eq(expected.getName()));
	EXPECT_THAT(arg.getBeginDate(), Eq(expected.getBeginDate()));
	return true;
}

class EditActionTests : public testing::Test
{
public:
	EditActionTests()
	{
		definitionDaoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&daoFactory, "habitDefinition");

		command.setCliParameters(&app);
		command.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getDefinition()
	{
		auto habitDefinition = std::make_unique<Entity::HabitDefinitionEntity>();
		habitDefinition->setId(1);
		habitDefinition->setName("definition name");
		habitDefinition->setBeginDate(Dt::parseDate("03.01.2019"));

		return habitDefinition;
	}

	CLI::App app;
	Dao::DaoFactory daoFactory;
	Commands::EditCommand command;
	std::shared_ptr<Mocks::HabitDefinitionDaoMock> definitionDaoMock;
};

TEST_F(EditActionTests, throws_action_error_when_no_filter_specified)
{
	try
	{
		parseArguments(&app, {"edit"});
		command.execute();
		FAIL() << "ActionError expected";
	}
	catch (CLI::ParseError& err)
	{
		auto expected = "--habit_id is required";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(EditActionTests, throws_action_error_when_nothing_to_change)
{
	try
	{
		parseArguments(&app, {"edit", "-i", "2"});
		command.execute();
		FAIL() << "ActionError expected";
	}
	catch (Actions::ActionError& err)
	{
		auto expected = "Nothing to change";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(EditActionTests, throws_error_when_habit_does_not_exist)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	try
	{
		parseArguments(&app, {"edit", "-i", "1", "--name", "My new name"});
		command.execute();
		FAIL() << "ActionError expected";
	}
	catch (Actions::ActionError& err)
	{
		auto expected = "Habit with id = 1 does not exist";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(EditActionTests, overrides_habit_name)
{
	auto expected = getDefinition();
	expected->setName("New definition name");

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(
		*definitionDaoMock, updateDefinition(DefinitionsAreEqual(*expected)));

	parseArguments(&app, {"edit", "-i", "1", "--name", "New definition name"});
	command.execute();
}

} // namespace Tests
