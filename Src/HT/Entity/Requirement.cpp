#include "HT/Entity/Requirement.h"

namespace Entity
{
Requirement::Requirement()
{
}

void Requirement::setHabitId(int id)
{
	habitId = id;
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

void Requirement::setEndDate(Dt::Date beginDate)
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
