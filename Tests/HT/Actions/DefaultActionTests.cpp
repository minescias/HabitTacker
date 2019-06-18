#include <gmock/gmock.h>

#include <Core/DateTime/DateTime.h>
#include <Core/DateTime/DateTimeGetter.h>

#include "HT/Actions/DefaultAction.h"
#include "HT/Actions/ActionError.h"
#include "HT/Dao/DaoFactory.h"

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

using namespace testing;

namespace Tests
{

class DefaultActionTest : public testing::Test
{
public:
	DefaultActionTest()
		: defaultAction()
	{
		habitDaoMock = registerAndGetDaoMock<Mocks::HabitDaoMock>(
			&daoFactory, "habit");
		definitionDaoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&daoFactory, "habitDefinition");

		defaultAction.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getHabitDefinition(
		int id, const std::string& name, int beginDateShift)
	{
		auto ts = Dt::Timestamp{1557014400};
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();

		entity->setId(id);
		entity->setName(name);
		entity->setBeginDate(Dt::DateTime{ts}.addDays(beginDateShift).unixTime());

		return entity;
	}

	std::vector<Entity::HabitDefinitionEntityPtr> getHabitDefinitions()
	{
		std::vector<Entity::HabitDefinitionEntityPtr> habits;
		habits.emplace_back(getHabitDefinition(1, "Pierwszy", -10));
		habits.emplace_back(getHabitDefinition(2, "Drugi", -50));
		return habits;
	}

	auto getHabit(int habitId, Dt::Timestamp date)
	{
		auto entity = std::make_unique<Entity::HabitEntity>();

		entity->setHabitId(habitId);
		entity->setDate(date);

		return entity;
	}

	std::vector<Entity::HabitEntityPtr> getHabits()
	{
		auto ts = Dt::Timestamp{1557014400};

		std::vector<Entity::HabitEntityPtr> habits;
		habits.emplace_back(getHabit(1, Dt::DateTime{ts}.unixTime()));
		habits.emplace_back(getHabit(1, Dt::DateTime{ts}.addDays(-2).unixTime()));
		habits.emplace_back(getHabit(2, Dt::DateTime{ts}.addDays(-1).unixTime()));
		habits.emplace_back(getHabit(2, Dt::DateTime{ts}.addDays(-2).unixTime()));
		habits.emplace_back(getHabit(2, Dt::DateTime{ts}.addDays(-10).unixTime()));
		habits.emplace_back(getHabit(2, Dt::DateTime{ts}.addDays(-12).unixTime()));

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
	auto day = Dt::Timestamp{1557014400}; // Niedziela/Sunday

	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	EXPECT_CALL(*habitDaoMock, getHabitsFromLastTwoWeeks(day))
		.WillOnce(Return(ByMove(getHabits())));

	auto expectedOutput =
		"\n  id name                                     Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su"
		"\n---- ---------------------------------------- -----------------------------------------"
		"\n   1 Pierwszy                                          __ __ __ __ __ __ __ __ XX __ XX"
		"\n   2 Drugi                                    __ XX __ XX __ __ __ __ __ __ __ XX XX __"
		"\n"
	;

	internal::CaptureStdout();

	defaultAction.execute(Cli::ParserResult("", "",
		Cli::Arguments{{"", "05-05-2019"}}));

	auto output = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(output.c_str(), expectedOutput);
}

TEST_F(DefaultActionTest, printsMessageWhenNoHabitsFound)
{
	EXPECT_CALL(*definitionDaoMock, getDefinitions()).WillOnce(
		Return(ByMove(std::vector<Entity::HabitDefinitionEntityPtr>())));

	try
	{
		defaultAction.execute(Cli::ParserResult("", "",
			Cli::Arguments{{"", "05-05-2019"}}));

		FAIL() << "Expected ActionError";
	}
	catch(const Actions::ActionError& err)
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

	defaultAction.execute(Cli::ParserResult("", "", Cli::Arguments{{"", ""}}));
}

} // namespace Tests
