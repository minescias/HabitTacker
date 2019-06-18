#include <gmock/gmock.h>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/EditAction.h"
#include "HT/Cli/ParserResult.h"
#include "HT/Dao/DaoFactory.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/DaoMockCreator.h"

namespace Tests
{

using namespace testing;

class EditActionTests : public testing::Test
{
public:
	EditActionTests()
	{
		daoFactory.registerDao("habitDefinition",
			[](Db::Database* db) -> Dao::UnknownDaoPtr
			{ return std::make_shared<Mocks::HabitDefinitionDaoMock>(db); });

		definitionDaoMock = daoFactory.createDao<Mocks::HabitDefinitionDaoMock>("habitDefinition");
		pr.arguments = Cli::Arguments{{"", ""}};
		action.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getDefinition()
	{
		auto habitDefinition = std::make_unique<Entity::HabitDefinitionEntity>();
		habitDefinition->setId(1);
		habitDefinition->setName("definition name");

		return habitDefinition;
	}

	Cli::ParserResult pr;
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
	catch(Actions::ActionError& err)
	{
		auto expected = "No filter specified";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(EditActionTests, throws_action_error_when_nothing_to_change)
{
	try
	{	pr.filter = 2;
		action.execute(pr);
		FAIL() << "ActionError expected";
	}
	catch(Actions::ActionError& err)
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
		pr.filter = "1";
		pr.arguments = Cli::Arguments{{"", ""}, {"name", "My new name"}};
		action.execute(pr);
		FAIL() << "ActionError expected";
	}
	catch(Actions::ActionError& err)
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

	pr.filter = "1";
	pr.arguments = Cli::Arguments{{"", ""}, {"name", "New definition name"}};
	action.execute(pr);
}

} // namespace Tests
