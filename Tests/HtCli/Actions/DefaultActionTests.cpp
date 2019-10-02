#include <gmock/gmock.h>

#include "Core/Dao/DaoFactory.h"
#include <Core/DateTime/AddDays.h>
#include <Core/DateTime/DateTimeGetter.h>

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/DefaultAction.h"

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{
using namespace date;
using namespace testing;

class DefaultActionTest : public testing::Test
{
public:
	DefaultActionTest() : defaultAction()
	{
		habitDaoMock =
			registerAndGetDaoMock<Mocks::HabitDaoMock>(&daoFactory, "habit");
		definitionDaoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&daoFactory, "habitDefinition");

		defaultAction.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getHabitDefinition(
		int id, const std::string& name, int beginDateShift)
	{
		auto date = 2019_y / May / 05_d;
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();

		entity->setId(id);
		entity->setName(name);
		entity->setBeginDate(Dt::addDays(date, beginDateShift));

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

	std::vector<Entity::HabitEntityPtr> getHabits()
	{
		auto date = 2019_y / May / 05_d;

		std::vector<Entity::HabitEntityPtr> habits;
		habits.emplace_back(getHabit(1, date));
		habits.emplace_back(getHabit(1, Dt::addDays(date, -2)));
		habits.emplace_back(getHabit(2, Dt::addDays(date, -1)));
		habits.emplace_back(getHabit(2, Dt::addDays(date, -2)));
		habits.emplace_back(getHabit(2, Dt::addDays(date, -10)));
		habits.emplace_back(getHabit(2, Dt::addDays(date, -12)));

		return habits;
	}

public:
	Dao::DaoFactory daoFactory;
	std::shared_ptr<Mocks::HabitDaoMock> habitDaoMock;
	std::shared_ptr<Mocks::HabitDefinitionDaoMock> definitionDaoMock;
	Actions::DefaultAction defaultAction;
};

TEST_F(DefaultActionTest, printsTableWithCurrentHabits)
{
	auto date = 2019_y / May / 05_d;

	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	EXPECT_CALL(*habitDaoMock, getHabitsFromLastTwoWeeks(date))
		.WillOnce(Return(ByMove(getHabits())));

	auto expectedOutput =
		"\n  id name                                     Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su"
		"\n---- ---------------------------------------- -----------------------------------------"
		"\n   1 Pierwszy                                          __ __ __ __ __ __ __ __ XX __ XX"
		"\n   2 Drugi zżź                                __ XX __ XX __ __ __ __ __ __ __ XX XX __"
		"\n";

	internal::CaptureStdout();

	auto pr = Cli::Parameters();
	pr.setDefaultParameter("05.05.2019");
	defaultAction.execute(pr);

	auto output = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(output.c_str(), expectedOutput);
}

TEST_F(DefaultActionTest, printsMessageWhenNoHabitsFound)
{
	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(std::vector<Entity::HabitDefinitionEntityPtr>())));

	try
	{
		auto pr = Cli::Parameters();
		pr.setDefaultParameter("05.05.2019");
		defaultAction.execute(pr);

		FAIL() << "Expected ActionError";
	}
	catch (const Actions::ActionError& err)
	{
		auto expected = "No habits found, try to add some using 'htr add'\n";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DefaultActionTest, printsHabitsForTodayByDefault)
{
	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	EXPECT_CALL(*habitDaoMock, getHabitsFromLastTwoWeeks(Dt::getCurrentDate()));

	defaultAction.execute(Cli::Parameters());
}

} // namespace Tests
