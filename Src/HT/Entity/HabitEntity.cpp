#include "HT/Entity/HabitEntity.h"

namespace Entity
{
HabitEntity::HabitEntity() : habitId(0), result(0)
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

int HabitEntity::getResult() const
{
	return result;
}

void HabitEntity::setResult(int result)
{
	this->result = result;
}

bool HabitEntity::operator==(const HabitEntity& rhs) const
{
	return getHabitId() == rhs.getHabitId() && getDate() == rhs.getDate()
		&& getResult() == rhs.getResult();
}

} // namespace Entity
