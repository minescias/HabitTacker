#include <gmock/gmock.h>

#include "HT/Actions/ActionError.h"
#include "HT/Actions/AddAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{

using namespace testing;

class AddActionTests : public testing::Test
{
public:
	AddActionTests()
	{
		daoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&factory, "habitDefinition");

		addAction.setDaoFactory(&factory);
		pr = Cli::ParserResult("add", "", Cli::Arguments{{"", ""}});
	}

	std::shared_ptr<Mocks::HabitDefinitionDaoMock> daoMock;
	Dao::DaoFactory factory;
	Actions::AddAction addAction;
	Cli::ParserResult pr;
};

TEST_F(AddActionTests, savesHabitToDatabase)
{
	Entity::HabitDefinitionEntity entity;
	entity.setName("new habit name");

	EXPECT_CALL(*daoMock, getDefinition("new habit name")).WillOnce(
		Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	EXPECT_CALL(*daoMock, saveDefinition(entity));

	pr.arguments = Cli::Arguments{{"", "new habit name"}};
	addAction.execute(pr);
}

TEST_F(AddActionTests, ensures_that_name_is_not_empty)
{
	try
	{
		addAction.execute(pr);
		FAIL() << "Action error expected";
	}
	catch(Actions::ActionError& err)
	{
		auto expected{"No habit name specified"};
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(AddActionTests, throw_error_when_adding_habit_that_already_esists)
{
	EXPECT_CALL(*daoMock, getDefinition("new habit name")).WillOnce(
		Return(ByMove(std::make_unique<Entity::HabitDefinitionEntity>())));

	try
	{
		pr.arguments = Cli::Arguments{{"", "new habit name"}};
		addAction.execute(pr);
		FAIL() << "Action error expected";
	}
	catch(Actions::ActionError& err)
	{
		auto expected{"Habit with name 'new habit name' already exists"};
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
