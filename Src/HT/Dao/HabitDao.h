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

	virtual void saveHabit(const Entity::HabitEntity& habit) const;
	virtual void deleteHabit(const Entity::HabitEntity& habit) const;

	virtual std::vector<Entity::HabitEntityPtr> getHabitsById(int id) const;
	virtual bool checkIfHabitIsSetForDay(const Entity::HabitEntity& habit) const;

	virtual std::vector<Entity::HabitEntityPtr> getHabits(int definitionId, 
		Dt::Date beginDate, Dt::Date endDate) const final;

private:
	Db::Database* db;
};

} // namespace Dao

#endif // __HABIT_DAO_H
