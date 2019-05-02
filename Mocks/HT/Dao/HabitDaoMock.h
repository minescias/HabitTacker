#ifndef __HABIT_DAO_MOCK_H
#define __HABIT_DAO_MOCK_H

#include <gmock/gmock.h>

#include "HT/Dao/IHabitDao.h"

namespace Mocks
{

class HabitDaoMock : public Dao::IHabitDao
{
public:
	MOCK_METHOD1(saveHabit, void(const Entity::HabitEntity& habit));
	MOCK_METHOD1(getHabitsById, std::vector<Entity::HabitEntityPtr> (int id));
	MOCK_METHOD1(checkIfHabitIsSetForDay, bool(const Entity::HabitEntity& habit));
};

} // namespace Mocks

#endif // __HABIT_DAO_MOCK_H
