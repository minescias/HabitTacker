#include "CLI/App.hpp"
#include "CLI/Error.hpp"
#include "gmock/gmock-matchers.h"
#include "gmock/gmock.h"

#include "Core/DateTime/DateTimeGetter.h"
#include "Core/DateTime/FormatDate.h"
#include "Core/DateTime/Operators.h"

#include "HtCli/Commands/CommandError.h"
#include "HtCli/Commands/DoneCommand.h"

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Mocks/HT/Dao/RequirementDaoMock.h"
#include "Tests/HtCli/Tools/CliTestTools.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace
{
using date::days;
using namespace testing;

MATCHER_P(habitPkEqual, expected, "")
{
	return arg.getHabitId() == expected.getHabitId()
		&& arg.getDate() == expected.getDate();
}

MATCHER_P(habitEqual, expected, "")
{
	EXPECT_THAT(arg.getHabitId(), Eq(expected.getHabitId()));
	EXPECT_THAT(arg.getDate(), Eq(expected.getDate()));
	EXPECT_THAT(arg.getResult(), Eq(arg.getResult()));

	return arg.getHabitId() == expected.getHabitId()
		&& arg.getDate() == expected.getDate()
		&& arg.getResult() == arg.getResult();
}

} // namespace

namespace Tests
{
class DoneCommandTests : public testing::Test
{
public:
	DoneCommandTests()
	{
		habitDaoMock =
			registerAndGetDaoMock<Mocks::HabitDaoMock>(&daoFactory, "habit");

		definitionDaoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&daoFactory, "habitDefinition");

		requirementDaoMock = registerAndGetDaoMock<Mocks::RequirementDaoMock>(
			&daoFactory, "requirement");

		doneCommand.setCliParameters(&app);
		doneCommand.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getDefinition() const
	{
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();
		entity->setId(1);
		entity->setName("name");
		entity->setBeginDate(Dt::getCurrentDate() - days{10});

		return entity;
	}

	CLI::App app;
	Commands::DoneCommand doneCommand;
	Dao::DaoFactory daoFactory;
	std::shared_ptr<Mocks::HabitDaoMock> habitDaoMock;
	std::shared_ptr<Mocks::HabitDefinitionDaoMock> definitionDaoMock;
	std::shared_ptr<Mocks::RequirementDaoMock> requirementDaoMock;
};

TEST_F(DoneCommandTests, setsHabitAsDoneForToday)
{
	auto currentTarget = 10;
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());
	habit.setResult(currentTarget);

	EXPECT_CALL(*requirementDaoMock, getCurrentTarget(1)).WillOnce(Return(currentTarget));
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));
	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habitPkEqual(habit)))
		.WillOnce(Return(false));
	EXPECT_CALL(*habitDaoMock, saveHabit(habitEqual(habit))).Times(1);

	parseArguments(&app, {"done", "-i", "1"});
	doneCommand.execute();
}

TEST_F(DoneCommandTests, deleteHabitForToday)
{
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(*habitDaoMock, deleteHabit(habit)).Times(1);

	parseArguments(&app, {"done", "-i", "1", "--reset"});
	doneCommand.execute();
}

TEST_F(DoneCommandTests, savesHabitUsingDateParam)
{
	auto currentTarget = 10;
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate() - days{1});
	habit.setResult(currentTarget);

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));
	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habitPkEqual(habit)))
		.WillOnce(Return(false));
	EXPECT_CALL(*requirementDaoMock, getCurrentTarget(1)).WillOnce(Return(currentTarget));
	EXPECT_CALL(*habitDaoMock, saveHabit(habit)).Times(1);

	parseArguments(&app, {"done", "-i", "1", "--date", "yesterday"});
	doneCommand.execute();
}

TEST_F(DoneCommandTests, saves_habit_using_result)
{
	auto resultSetByUser = 8;
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());
	habit.setResult(resultSetByUser);

	EXPECT_CALL(*habitDaoMock, saveHabit(habit)).Times(1);
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));
	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habitPkEqual(habit)))
		.WillOnce(Return(false));

	parseArguments(&app, {"done", "-i", "1", "-r", "8"});
	doneCommand.execute();
}

TEST_F(DoneCommandTests, ensuresThatHabisWasNotSetPreviously)
{
	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	EXPECT_CALL(*habitDaoMock, checkIfHabitIsSetForDay(habit)).WillOnce(Return(true));

	try
	{
		parseArguments(&app, {"done", "-i", "1"});
		doneCommand.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const Commands::CommandError& err)
	{
		auto expected = "Habit 1 was already set for this day";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneCommandTests, ensuresThatHabisExists)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(2))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	try
	{
		parseArguments(&app, {"done", "-i", "2"});
		doneCommand.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const Commands::CommandError& err)
	{
		auto expected = "Habit 2 does not exist";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneCommandTests, ensures_that_habit_is_set)
{
	try
	{
		parseArguments(&app, {"done"});
		doneCommand.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const CLI::ParseError& err)
	{
		auto expected = "--habit_id is required";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DoneCommandTests, cannot_done_habit_before_begin_date)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	auto dateStr = Dt::formatDate(Dt::getCurrentDate() - days{11});

	try
	{
		parseArguments(&app, {"done", "-i", "1", "--date", dateStr});
		doneCommand.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const Commands::CommandError& err)
	{
		auto expected = "Cannot set habit before it's begin date which is "
			+ Dt::formatDate(Dt::getCurrentDate() - days{10});

		ASSERT_THAT(expected, Eq(err.what()));
	}
}

TEST_F(DoneCommandTests, cannot_done_habit_in_the_future)
{
	EXPECT_CALL(*definitionDaoMock, getDefinition(1))
		.WillOnce(Return(ByMove(getDefinition())));

	try
	{
		parseArguments(&app, {"done", "-i", "1", "--date", "tomorrow"});
		doneCommand.execute();
		FAIL() << "Expected ActionError";
	}
	catch (const Commands::CommandError& err)
	{
		auto expected = "Cannot set habit in the future";
		ASSERT_STREQ(expected, err.what());
	}
}

} // namespace Tests
