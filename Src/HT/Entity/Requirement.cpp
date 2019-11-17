#include "HT/Entity/Requirement.h"

namespace Entity
{
Requirement::Requirement()
{
}

void Requirement::setId(int id)
{
	this->id = id;
}
int Requirement::getId() const
{
	return id;
}

void Requirement::setHabitId(int habitId)
{
	this->habitId = habitId;
}

int Requirement::getHabitId() const
{
	return habitId;
}

void Requirement::setBeginDate(Dt::Date beginDate)
{
	this->beginDate = beginDate;
}

Dt::Date Requirement::getBeginDate() const
{
	return beginDate;
}

void Requirement::setEndDate(Dt::Date endDate)
{
	this->endDate = endDate;
}

Dt::Date Requirement::getEndDate() const
{
	return endDate;
}

void Requirement::setTarget(int target)
{
	this->target = target;
}

int Requirement::getTarget() const
{
	return target;
}

} // namespace Entity
