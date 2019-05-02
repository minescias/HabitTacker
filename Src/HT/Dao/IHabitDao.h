#ifndef __I_HABIT_DAO_H
#define __I_HABIT_DAO_H

#include "HT/Entity/HabitEntity.h"

#include <vector>

namespace Dao
{

class IHabitDao
{
public:
	virtual void saveHabit(const Entity::HabitEntity& habit) = 0;
	virtual std::vector<Entity::HabitEntityPtr> getHabitsById(int id) = 0;
	virtual bool checkIfHabitIsSetForDay(const Entity::HabitEntity& habit) = 0;
};

} // namespace Dao

#endif __I_HABIT_DAO_H