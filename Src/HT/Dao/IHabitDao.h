#ifndef __I_HABIT_DAO_H
#define __I_HABIT_DAO_H

#include <vector>

#include "HT/Dao/UnknownDao.h"
#include "HT/Entity/HabitEntity.h"

namespace Dao
{

class IHabitDao : public UnknownDao
{
public:
	virtual void saveHabit(const Entity::HabitEntity& habit) = 0;
	virtual void deleteHabit(const Entity::HabitEntity& habit) = 0;

	virtual std::vector<Entity::HabitEntityPtr> getHabitsById(int id) = 0;
	virtual bool checkIfHabitIsSetForDay(const Entity::HabitEntity& habit) = 0;
	virtual std::vector<Entity::HabitEntityPtr> getHabitsFromLastTwoWeeks(Dt::Timestamp date) = 0;

	virtual ~IHabitDao(){};
};

} // namespace Dao

#endif // __I_HABIT_DAO_H
