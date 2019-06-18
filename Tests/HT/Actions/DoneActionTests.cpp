#include <gmock/gmock.h>

#include "Core/DateTime/DateTime.h"
#include "Core/DateTime/DateTimeGetter.h"

#include "HT/Actions/DoneAction.h"
#include "HT/Actions/ActionError.h"

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/DaoMockCreator.h"

using namespace testing;

namespace Tests
{

class DoneActionTest : public testing::Test
{
public:
	DoneActionTest()
		: doneAction()
	{
		daoFactory.registerDao("habit",
			[](Db::Database* db) -> Dao::UnknownDaoPtr
			{ return std::make_shared<Mocks::HabitDaoMock>(db); });

		daoFactory.registerDao("habitDefinition",
			[](Db::Database* db) -> Dao::UnknownDaoPtr
			{ return std::make_shared<Mocks::HabitDefinitionDaoMock>(db); });

		habitDaoMock = daoFactory.createDao<Mocks::HabitDaoMock>("habit");
		definitionDaoMock = daoFactory.createDao<Mocks::HabitDefinitionDaoMock>("habitDefinition");

		doneAction.setDaoFactory(&daoFactory);

		pr.filter = "1";
	}

	Entity::HabitDefinitionEntityPtr getDefinition()
	{
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();
		entity->setId(1);
		entity->setName("name");
		entity->setBeginDate(Dt::getCurrentDateShiftByDays(-10));

		return entity;
	}

	Dao::DaoFactory daoFactory;
	std::shared_ptr<Mocks::HabitDaoMock> habitDaoMock;
	std::shared_ptr<Mocks::HabitDefinitionDaoMock> definitionDaoMock;
	Actions::DoneAction doneAction;
	Cli::ParserResult pr;
};

TEST_F(DoneActionTest, setsHabitAsDoneForToday)
{
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(*habitDaoMock, saveHabit(habit)).Times(1);
	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habit))
		.WillOnce(Return(false));

	doneAction.execute(pr);
}

TEST_F(DoneActionTest, deleteHabitForToday)
{
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(*habitDaoMock, deleteHabit(habit)).Times(1);

	pr.arguments = Cli::Arguments{{"reset", ""}};
	doneAction.execute(pr);
}

TEST_F(DoneActionTest, savesHabitUsingDateParam)
{
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDateShiftByDays(-1));

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habit))
		.WillOnce(Return(false));

	EXPECT_CALL(*habitDaoMock, saveHabit(habit)).Times(1);

	pr.arguments = Cli::Arguments{{"date", "yesterday"}};
	doneAction.execute(pr);
}

TEST_F(DoneActionTest, ensuresThatHabisWasNotSetPreviously)
{
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habit))
		.WillOnce(Return(true));

	try
	{
		doneAction.execute(pr);
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		auto expected = "Habit 1 was already set for this day";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneActionTest, ensuresThatHabisExists)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(2))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	try
	{
		pr.filter = "2";
		doneAction.execute(pr);
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		auto expected = "Habit 2 does not exist";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneActionTest, ensuresThatFilterIsSet)
{
	try
	{
		doneAction.execute(Cli::ParserResult());
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		auto expected = "No filter specified";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneActionTest, cannot_done_habit_before_begin_date)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	auto dateStr = Dt::DateTime(Dt::getCurrentDateShiftByDays(-11)).dateString();

	try
	{
		pr.arguments = Cli::Arguments{{"", ""}, {"date", dateStr}};
		doneAction.execute(pr);
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		auto expected = "Cannot set habit before it's begin date which is " +
			Dt::DateTime(Dt::getCurrentDateShiftByDays(-10)).dateString();

		ASSERT_THAT(expected, Eq(err.what()));
	}
}

TEST_F(DoneActionTest, cannot_done_habit_in_the_future)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	try
	{
		pr.arguments = Cli::Arguments{{"", ""}, {"date", "tomorrow"}};
		doneAction.execute(pr);
		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
	{
		auto expected = "Cannot set habit in the future";
		ASSERT_STREQ(expected, err.what());
	}
}

} //namespace Tests
