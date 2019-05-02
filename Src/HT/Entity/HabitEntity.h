#ifndef __HABIT_ENTITY_H
#define __HABIT_ENTITY_H

#include <ctime>
#include <memory>

using Date = time_t;

namespace Entity
{

class HabitEntity
{
public:
	HabitEntity();

	int getHabitId() const;
	void setHabitId(int id);

	Date getDate() const;
	void setDate(const Date& date);

private:
	int habitId;
	Date date;
};

bool operator==(const HabitEntity &a, const HabitEntity &b);

using HabitEntityPtr = std::unique_ptr<HabitEntity>	;

} // namespace Entity

#endif
