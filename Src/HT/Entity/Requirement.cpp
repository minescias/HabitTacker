#include "HT/Entity/Requirement.h"

namespace Entity
{
Requirement::Requirement() : id(0), habitId(0), target(0)
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

void Requirement::setEndDate(std::optional<Dt::Date> endDate)
{
	this->endDate = endDate;
}

std::optional<Dt::Date> Requirement::getEndDate() const
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

bool Requirement::operator==(const Requirement& rhs) const
{
	// clang-format off
	return 
		id == rhs.id
		&& habitId == rhs.habitId
		&& beginDate == rhs.beginDate
		&& endDate == rhs.endDate
		&& target == rhs.target;
	// clang-format on
}

} // namespace Entity
