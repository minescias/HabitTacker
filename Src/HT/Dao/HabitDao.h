#ifndef __HABIT_DAO_H
#define __HABIT_DAO_H

#include <Core/Database/Database_fwd.h>

#include "HT/Dao/IHabitDao.h"

namespace Dao
{

class HabitDao : public IHabitDao
{
public:
	HabitDao(Db::Database* db);

	virtual void saveHabit(const Entity::HabitEntity& habit);
	virtual std::vector<Entity::HabitEntityPtr> getHabitsById(int id);
	virtual bool checkIfHabitIsSetForDay(const Entity::HabitEntity& habit);

private:
	Db::Database* db;
};

} // namespace Dao

#endif __HABIT_DAO_H