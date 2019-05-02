#include <gmock/gmock.h>

#include "Mocks/HT/Dao/HabitDaoMock.h"

#include "HT/Actions/DoneAction.h"

using namespace testing;

class DoneActionTest : public testing::Test
{
public:
	DoneActionTest()
		: doneAction(&habitDaoMock)
	{
	}

	Mocks::HabitDaoMock habitDaoMock;
	Actions::DoneAction doneAction;
};

TEST_F(DoneActionTest, setsHabitAsDoneForToday)
{
	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(today);

	EXPECT_CALL(habitDaoMock, saveHabit(habit)).Times(1);
	doneAction.execute("1");
}