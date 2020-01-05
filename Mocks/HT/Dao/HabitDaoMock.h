#ifndef __HABIT_DAO_MOCK_H
#define __HABIT_DAO_MOCK_H

#include <gmock/gmock.h>

#include "HT/Dao/IHabitDao.h"

namespace Mocks
{
class HabitDaoMock : public Dao::IHabitDao
{
public:
	MOCK_METHOD(void, saveHabit, (const Entity::HabitEntity& habit), (const, override));
	MOCK_METHOD(void, deleteHabit, (const Entity::HabitEntity& habit), (const, override));

	MOCK_METHOD(
		std::vector<Entity::HabitEntityPtr>,
		getHabitsById,
		(int id),
		(const, override));

	MOCK_METHOD(
		bool,
		checkIfHabitIsSetForDay,
		(const Entity::HabitEntity& habit),
		(const, override));

	MOCK_METHOD(
		std::vector<Entity::HabitEntityPtr>,
		getHabits,
		(int id, Dt::Date beginDate, Dt::Date endDate),
		(const, override));
};

} // namespace Mocks

#endif // __HABIT_DAO_MOCK_H
