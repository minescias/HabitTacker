#ifndef __HABIT_ENTITY_H
#define __HABIT_ENTITY_H

#include <chrono>

using Date = std::chrono::system_clock::time_point;

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

} // namespace Entity

#endif
