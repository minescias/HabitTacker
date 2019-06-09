#include "HT/Entity/HabitDefinitionEntity.h"

namespace Entity
{

HabitDefinitionEntity::HabitDefinitionEntity()
	: id(0)
	, beginDate(0)
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

void HabitDefinitionEntity::setBeginDate(Dt::Timestamp date)
{
	this->beginDate = date;
}

Dt::Timestamp HabitDefinitionEntity::getBeginDate() const
{
	return beginDate;
}

bool operator==(const HabitDefinitionEntity &a, const HabitDefinitionEntity &b)
{
	return a.getId() == b.getId()
		&& a.getName() == b.getName()
		&& a.getBeginDate() == b.getBeginDate();
}

} // namespace Entity
