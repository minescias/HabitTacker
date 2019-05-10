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

void AddAction::execute(const Cli::ParserResult& parserResult)
{
	auto habitDefinition = Entity::HabitDefinitionEntity();
	habitDefinition.setName(parserResult.argument);

	dao->saveDefinition(habitDefinition);
}

} // namespace Actions


