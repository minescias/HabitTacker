#include <gmock/gmock.h>

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"

#include "HT/Actions/DoneAction.h"
#include "HT/Actions/ActionError.h"

using namespace testing;

class DoneActionTest : public testing::Test
{
public:
	DoneActionTest()
		: doneAction(&habitDaoMock, &definitionDaoMock)
	{
	}

	Mocks::HabitDaoMock habitDaoMock;
	Mocks::HabitDefinitionDaoMock definitionDaoMock;
	Actions::DoneAction doneAction;
};

TEST_F(DoneActionTest, setsHabitAsDoneForToday)
{
	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(today);

	EXPECT_CALL(definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(std::make_unique<Entity::HabitDefinitionEntity>())));

	EXPECT_CALL(habitDaoMock, saveHabit(habit)).Times(1);
	EXPECT_CALL(habitDaoMock, checkIfHabitIsSetForDay(habit))
		.WillOnce(Return(false));

	doneAction.execute("1");
}

TEST_F(DoneActionTest, ensuresThatHabisWasNotSetPreviously)
{
	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(today);

	EXPECT_CALL(definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(std::make_unique<Entity::HabitDefinitionEntity>())));

	EXPECT_CALL(habitDaoMock, checkIfHabitIsSetForDay(habit))
		.WillOnce(Return(true));

	try
	{
		doneAction.execute("1");
		FAIL() << "Expected ActionError";
	}
	catch(const ActionError& err)
	{
		auto expected = "Habit 1 was already set for this day";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneActionTest, ensuresThatHabisExists)
{
	EXPECT_CALL(definitionDaoMock, getDefinition(2))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	try
	{
		doneAction.execute("2");
		FAIL() << "Expected ActionError";
	}
	catch(const ActionError& err)
	{
		auto expected = "Habit 2 does not exist";
		ASSERT_STREQ(expected, err.what());
	}
}