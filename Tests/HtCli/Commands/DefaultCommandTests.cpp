#include <gmock/gmock.h>

#include "CLI/App.hpp"

#include "Core/Dao/DaoFactory.h"
#include "Core/DateTime/DateTimeGetter.h"
#include "Core/DateTime/Operators.h"

#include "HtCli/Commands/CommandError.h"
#include "HtCli/Commands/ShowCommand.h"

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/HtCli/Tools/CliTestTools.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{
using namespace date;
using namespace testing;

class DefaultActionTest : public testing::Test
{
public:
	DefaultActionTest() : showCommand()
	{
		habitDaoMock =
			registerAndGetDaoMock<Mocks::HabitDaoMock>(&daoFactory, "habit");
		definitionDaoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&daoFactory, "habitDefinition");

		showCommand.setDaoFactory(&daoFactory);
		showCommand.setCliParameters(&app);
	}

	Entity::HabitDefinitionEntityPtr getHabitDefinition(
		int id, const std::string& name, int beginDateShift)
	{
		auto date = 2019_y / May / 05_d;
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();

		entity->setId(id);
		entity->setName(name);
		entity->setBeginDate(date + days{beginDateShift});

		return entity;
	}

	std::vector<Entity::HabitDefinitionEntityPtr> getHabitDefinitions()
	{
		std::vector<Entity::HabitDefinitionEntityPtr> habits;
		habits.emplace_back(getHabitDefinition(1, "Pierwszy", -10));
		habits.emplace_back(getHabitDefinition(2, "Drugi zżź", -50));
		return habits;
	}

	auto getHabit(int habitId, Dt::Date date)
	{
		auto entity = std::make_unique<Entity::HabitEntity>();

		entity->setHabitId(habitId);
		entity->setDate(date);

		return entity;
	}

	std::vector<Entity::HabitEntityPtr> getHabits1()
	{
		auto date = 2019_y / May / 05_d;

		std::vector<Entity::HabitEntityPtr> habits;
		habits.emplace_back(getHabit(1, date));
		habits.emplace_back(getHabit(1, date - days{2}));

		return habits;
	}

	std::vector<Entity::HabitEntityPtr> getHabits2()
	{
		auto date = 2019_y / May / 05_d;

		std::vector<Entity::HabitEntityPtr> habits;
		habits.emplace_back(getHabit(2, date - days{1}));
		habits.emplace_back(getHabit(2, date - days{2}));
		habits.emplace_back(getHabit(2, date - days{10}));
		habits.emplace_back(getHabit(2, date - days{12}));

		return habits;
	}

public:
	CLI::App app;
	Dao::DaoFactory daoFactory;
	std::shared_ptr<Mocks::HabitDaoMock> habitDaoMock;
	std::shared_ptr<Mocks::HabitDefinitionDaoMock> definitionDaoMock;
	Commands::ShowCommand showCommand;
};

TEST_F(DefaultActionTest, printsTableWithCurrentHabits)
{
	auto date = 2019_y / May / 05_d;

	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	EXPECT_CALL(*habitDaoMock, getHabits(1, date - days{14}, date))
		.WillOnce(Return(ByMove(getHabits1())));

	EXPECT_CALL(*habitDaoMock, getHabits(2, date - days{14}, date))
		.WillOnce(Return(ByMove(getHabits2())));

	auto expectedOutput =
		"\nId Name      Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su"
		"\n-- --------- -- -- -- -- -- -- -- -- -- -- -- -- -- --"
		"\n1  Pierwszy           __ __ __ __ __ __ __ __ XX __ XX"
		"\n2  Drugi zżź __ XX __ XX __ __ __ __ __ __ __ XX XX __"
		"\n";

	internal::CaptureStdout();

	parseArguments(&app, {"show", "-d", "05.05.2019"});
	showCommand.execute();

	auto output = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(output.c_str(), expectedOutput);
}

TEST_F(DefaultActionTest, printsMessageWhenNoHabitsFound)
{
	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(std::vector<Entity::HabitDefinitionEntityPtr>())));

	try
	{
		parseArguments(&app, {"show", "-d", "05.05.2019"});
		showCommand.execute();

		FAIL() << "Expected ActionError";
	}
	catch (const Commands::CommandError& err)
	{
		auto expected = "No habits found, try to add some using 'htr add'\n";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DefaultActionTest, printsHabitsForTodayByDefault)
{
	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	auto today = Dt::getCurrentDate();

	EXPECT_CALL(*habitDaoMock, getHabits(1, today - days{14}, today));
	EXPECT_CALL(*habitDaoMock, getHabits(2, today - days{14}, today));

	parseArguments(&app, {});
	showCommand.execute();
}

} // namespace Tests
