#include <HT/Actions/AddAction.h>

#include <iostream>

namespace Actions
{

AddAction::AddAction()
{
}

void AddAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
}

void AddAction::execute(const std::string& habitName)
{
	auto habitDefinition = Entity::HabitDefinitionEntity();
	habitDefinition.setName(habitName);

	dao->saveDefinition(habitDefinition);
}

} // namespace Actions


