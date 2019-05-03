#include <gmock/gmock.h>

#include "Mocks/HT/Dao/HabitDaoMock.h"
#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"

#include "HT/Actions/DefaultAction.h"
#include "HT/Actions/ActionError.h"

using namespace testing;

class DefaultActionTest : public testing::Test
{
public:
	DefaultActionTest()
		: defaultAction(&habitDaoMock, &definitionDaoMock)
	{
	}

	Entity::HabitDefinitionEntityPtr getHabit(int id, const std::string& name)
	{
		auto entity = std::make_unique<Entity::HabitDefinitionEntity>();

		entity->setId(id);
		entity->setName(name);

		return entity;
	}

	std::vector<Entity::HabitDefinitionEntityPtr> getHabits()
	{
		std::vector<Entity::HabitDefinitionEntityPtr> habits;
		habits.emplace_back(getHabit(1, "Pierwszy"));
		habits.emplace_back(getHabit(2, "Drugi"));

		return habits;
	}

public:
	Mocks::HabitDaoMock habitDaoMock;
	Mocks::HabitDefinitionDaoMock definitionDaoMock;
	Actions::DefaultAction defaultAction;
};

TEST_F(DefaultActionTest, printsTableWithCurrentHabits)
{
	EXPECT_CALL(definitionDaoMock, getDefinitions()).WillOnce(
		Return(ByMove(getHabits())));

	auto expectedOutput =
		"\nid   name"
		"\n---- ----------------------------------------"
		"\n   1 Pierwszy"
		"\n   2 Drugi"
		"\n"
	;

	internal::CaptureStdout();
	defaultAction.execute();
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(output.c_str(), expectedOutput);

	// auto today = time(nullptr);
	// today -= (today % 86400); // 86400 = 24 * 60 * 60

	// auto habit = Entity::HabitEntity();
	// habit.setHabitId(1);
	// habit.setDate(today);

	// EXPECT_CALL(definitionDaoMock, getDefinition(1))
	// 	.WillOnce(Return(ByMove(std::make_unique<Entity::HabitDefinitionEntity>())));

	// EXPECT_CALL(habitDaoMock, saveHabit(habit)).Times(1);
	// EXPECT_CALL(habitDaoMock, checkIfHabitIsSetForDay(habit))
	// 	.WillOnce(Return(false));

	// doneAction.execute("1");
}