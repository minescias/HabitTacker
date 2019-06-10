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

void AddAction::execute(const Cli::ParserResult& parserResult)
{
	auto newHabitName = parserResult.arguments.at("");
	if (newHabitName.empty())
		throw ActionError("No habit name specified");

	auto habitDefinition = Entity::HabitDefinitionEntity();
	habitDefinition.setName(parserResult.arguments.at(""));

	dao->saveDefinition(habitDefinition);
}

} // namespace Actions


