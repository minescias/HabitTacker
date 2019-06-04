#ifndef __HABIT_DAO_MOCK_H
#define __HABIT_DAO_MOCK_H

#include <gmock/gmock.h>

#include "HT/Dao/IHabitDao.h"

namespace Mocks
{

class HabitDaoMock : public Dao::IHabitDao
{
public:
	MOCK_CONST_METHOD1(saveHabit, void(const Entity::HabitEntity& habit));
	MOCK_CONST_METHOD1(deleteHabit, void(const Entity::HabitEntity& habit));
	MOCK_CONST_METHOD1(getHabitsById, std::vector<Entity::HabitEntityPtr> (int id));
	MOCK_CONST_METHOD1(checkIfHabitIsSetForDay, bool(const Entity::HabitEntity& habit));
	MOCK_CONST_METHOD1(getHabitsFromLastTwoWeeks, std::vector<Entity::HabitEntityPtr>(Dt::Timestamp date));
};

} // namespace Mocks

#endif // __HABIT_DAO_MOCK_H
