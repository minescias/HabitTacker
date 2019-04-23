#include "HT/Entity/HabitDefinitionEntity.h"

namespace Entity
{

HabitDefinitionEntity::HabitDefinitionEntity()
	:id(0)
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

bool operator==(const HabitDefinitionEntity &a, const HabitDefinitionEntity &b)
{
	return a.getId() == b.getId()
		&& a.getName() == b.getName();
}

} // namespace Entity


