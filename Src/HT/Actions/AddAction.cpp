#include <HT/Actions/AddAction.h>

#include <iostream>

namespace Actions
{

AddAction::AddAction(Dao::IHabitDefinitionDao* dao)
	: dao(dao)
{
}

void AddAction::execute(const std::string& habitName)
{
	auto habitDefinition = Entity::HabitDefinitionEntity();
	habitDefinition.setName(habitName);

	dao->saveDefinition(habitDefinition);
}

} // namespace Actions


