#include "HT/Entity/HabitEntity.h"

namespace Entity
{

HabitEntity::HabitEntity()
	: habitId(0)
{
}

int HabitEntity::getHabitId() const
{
	return habitId;
}

void HabitEntity::setHabitId(int id)
{
	habitId = id;
}

Date HabitEntity::getDate() const
{
	return date;
}

void HabitEntity::setDate(const Date& date)
{
	this->date = date;
}

} // namespace Entity

