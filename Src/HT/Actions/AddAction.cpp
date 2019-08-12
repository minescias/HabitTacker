#include <HT/Actions/AddAction.h>

#include <HT/Actions/ActionError.h>

namespace Actions
{

AddAction::AddAction()
{
}

void AddAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
}

void AddAction::execute(const Cli::Parameters& parserResult)
{
	auto name = parserResult.getDefaultParameter();

	if (name.empty())
		throw ActionError("No habit name specified");

	auto existingDefinition = dao->getDefinition(name);
	if (existingDefinition)
		throw ActionError("Habit with name '" + name + "' already exists");

	auto newDefinition = Entity::HabitDefinitionEntity();
	newDefinition.setName(name);
	dao->saveDefinition(newDefinition);
}

} // namespace Actions


