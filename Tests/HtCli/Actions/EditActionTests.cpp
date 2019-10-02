#include <gmock/gmock.h>

#include "Core/Cli/Parameters.h"
#include "Core/Dao/DaoFactory.h"

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/EditAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{
using namespace testing;

class EditActionTests : public testing::Test
{
public:
	EditActionTests()
	{
		definitionDaoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&daoFactory, "habitDefinition");

		action.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getDefinition()
	{
		auto habitDefinition = std::make_unique<Entity::HabitDefinitionEntity>();
		habitDefinition->setId(1);
		habitDefinition->setName("definition name");

		return habitDefinition;
	}

	Cli::Parameters pr;
	Dao::DaoFactory daoFactory;
	Actions::EditAction action;
	std::shared_ptr<Mocks::HabitDefinitionDaoMock> definitionDaoMock;
};

TEST_F(EditActionTests, throws_action_error_when_no_filter_specified)
{
	try
	{
		action.execute(pr);
		FAIL() << "ActionError expected";
	}
	catch (RuntimeError& err)
	{
		auto expected = "No filter specified";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(EditActionTests, throws_action_error_when_nothing_to_change)
{
	try
	{
		pr.setFilter("2");
		action.execute(pr);
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
		pr.setFilter("1");
		pr.setParameter("name", "My new name");
		action.execute(pr);
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

	EXPECT_CALL(*definitionDaoMock, updateDefinition(*expected));

	pr.setFilter("1");
	pr.setParameter("name", "New definition name");
	action.execute(pr);
}

} // namespace Tests
