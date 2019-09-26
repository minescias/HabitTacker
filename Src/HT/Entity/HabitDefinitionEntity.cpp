#include "HT/Entity/HabitDefinitionEntity.h"

namespace Entity
{
HabitDefinitionEntity::HabitDefinitionEntity() : id(0)
{
}

void HabitDefinitionEntity::setId(int id)
{
	this->id = id;
}

int HabitDefinitionEntity::getId() const
{
	return id;
}

void HabitDefinitionEntity::setName(const std::string& name)
{
	this->name = name;
}

std::string HabitDefinitionEntity::getName() const
{
	return name;
}

void HabitDefinitionEntity::setBeginDate(Dt::Date date)
{
	this->beginDate = date;
}

Dt::Date HabitDefinitionEntity::getBeginDate() const
{
	return beginDate;
}

bool operator==(const HabitDefinitionEntity& a, const HabitDefinitionEntity& b)
{
	// TODO: custom method to compare dates
	return a.getId() == b.getId() && a.getName() == b.getName()
		&& ((!a.getBeginDate().ok() && !b.getBeginDate().ok())
			|| a.getBeginDate() == b.getBeginDate());
}

} // namespace Entity
