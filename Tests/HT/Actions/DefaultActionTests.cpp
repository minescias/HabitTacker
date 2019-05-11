#include <gmock/gmock.h>

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"

#include "HT/Actions/DefaultAction.h"
#include "HT/Actions/ActionError.h"
#include "HT/Dao/DaoFactory.h"

#include "Tests/Tools/DaoMockCreator.h"

using namespace testing;

namespace Tests
{

class DefaultActionTest : public testing::Test
{
public:
	DefaultActionTest()
		: defaultAction()
	{
		habitDaoMock = new Mocks::HabitDaoMock();
		definitionDaoMock = new Mocks::HabitDefinitionDaoMock();

		daoFactory.registerDao("habit", createDaoMock(habitDaoMock));
		daoFactory.registerDao("habitDefinition", createDaoMock(definitionDaoMock));

		defaultAction.setDaoFactory(&daoFactory);
	}

	Entity::HabitDefinitionEntityPtr getHabitDefinition(int id, const std::string& name)
	{
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();

		entity->setId(id);
		entity->setName(name);

		return entity;
	}

	std::vector<Entity::HabitDefinitionEntityPtr> getHabitDefinitions()
	{
		std::vector<Entity::HabitDefinitionEntityPtr> habits;
		habits.emplace_back(getHabitDefinition(1, "Pierwszy"));
		habits.emplace_back(getHabitDefinition(2, "Drugi"));

		return habits;
	}

	auto getHabit(int habitId, time_t date)
	{
		auto entity = std::make_unique<Entity::HabitEntity>();

		entity->setHabitId(habitId);
		entity->setDate(date);

		return entity;
	}

	std::vector<Entity::HabitEntityPtr> getHabits()
	{
		auto secondsInDay{86400};	// 86400 = 24 * 60 * 60
		auto day = time_t{1557014400}; // Niedziela/Sunday

		std::vector<Entity::HabitEntityPtr> habits;
		habits.emplace_back(getHabit(1, day));
		habits.emplace_back(getHabit(1, day - secondsInDay * 2));
		habits.emplace_back(getHabit(2, day - secondsInDay * 1));
		habits.emplace_back(getHabit(2, day - secondsInDay * 2));
		habits.emplace_back(getHabit(2, day - secondsInDay * 10));
		habits.emplace_back(getHabit(2, day - secondsInDay * 12));

		return habits;
	}

public:
	Dao::DaoFactory daoFactory;
	Mocks::HabitDaoMock* habitDaoMock;
	Mocks::HabitDefinitionDaoMock* definitionDaoMock;
	Actions::DefaultAction defaultAction;
};

TEST_F(DefaultActionTest, printsTableWithCurrentHabits)
{
	auto day = time_t{1557014400}; // Niedziela/Sunday

	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	EXPECT_CALL(*habitDaoMock, getHabitsFromLastTwoWeeks(day))
		.WillOnce(Return(ByMove(getHabits())));

	auto expectedOutput =
		"\n  id name                                     Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su"
		"\n---- ---------------------------------------- -----------------------------------------"
		"\n   1 Pierwszy                                 __ __ __ __ __ __ __ __ __ __ __ XX __ XX"
		"\n   2 Drugi                                    __ XX __ XX __ __ __ __ __ __ __ XX XX __"
		"\n"
	;

	internal::CaptureStdout();
	defaultAction.execute(Cli::ParserResult("", "", "05-05-2019"));
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(output.c_str(), expectedOutput);
}

TEST_F(DefaultActionTest, printsMessageWhenNoHabitsFound)
{
	EXPECT_CALL(*definitionDaoMock, getDefinitions()).WillOnce(
		Return(ByMove(std::vector<Entity::HabitDefinitionEntityPtr>())));

	try
	{
		defaultAction.execute(Cli::ParserResult("", "", "05-05-2019"));
		FAIL() << "Expected ActionError";
	}
	catch(const ActionError& err)
	{
		auto expected = "No habits found, try to add some using 'ht add'\n";
		ASSERT_STREQ(expected, err.what());
	}
}

TEST_F(DefaultActionTest, printsHabitsForTodayByDefault)
{
	auto today = time(nullptr);
	auto secondsInDay{86400};	// 86400 = 24 * 60 * 60
	today -= (today % secondsInDay);

	EXPECT_CALL(*definitionDaoMock, getDefinitions())
		.WillOnce(Return(ByMove(getHabitDefinitions())));

	EXPECT_CALL(*habitDaoMock, getHabitsFromLastTwoWeeks(today)).Times(1);

	defaultAction.execute(Cli::ParserResult("", "", ""));
}

} // namespace Tests
