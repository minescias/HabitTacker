#ifndef __HABIT_ENTITY_H
#define __HABIT_ENTITY_H

#include <memory>

#include <Core/DateTime/Date.h>

namespace Entity
{
class HabitEntity
{
public:
	HabitEntity();

	int getHabitId() const;
	void setHabitId(int id);

	Dt::Date getDate() const;
	void setDate(const Dt::Date& date);

private:
	int habitId;
	Dt::Date date;
};

bool operator==(const HabitEntity& a, const HabitEntity& b);

using HabitEntityPtr = std::unique_ptr<HabitEntity>;

} // namespace Entity

#endif
