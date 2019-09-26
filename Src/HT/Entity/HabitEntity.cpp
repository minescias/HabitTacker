#include "HT/Entity/HabitEntity.h"

namespace Entity
{
HabitEntity::HabitEntity() : habitId(0)
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

Dt::Date HabitEntity::getDate() const
{
	return date;
}

void HabitEntity::setDate(const Dt::Date& date)
{
	this->date = date;
}

bool operator==(const HabitEntity& a, const HabitEntity& b)
{
	return a.getHabitId() == b.getHabitId() && a.getDate() == b.getDate();
}

} // namespace Entity
