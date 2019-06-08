#include "HT/Actions/EditAction.h"

#include "HT/Actions/ActionError.h"

namespace Actions
{

EditAction::EditAction()
{
}

void EditAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
}

void EditAction::execute(const Cli::ParserResult& parserResult)
{
	auto habitId = parserResult.filter;
	if (habitId.empty())
		throw ActionError("No filter specified");

	if (parserResult.arguments.size() == 1)
		throw ActionError("Nothing to change");

	auto defintion = dao->getDefinition(std::stoi(habitId));

	if (!defintion)
		throw ActionError("Habit with id = " + habitId + " does not exist") ;

	if (parserResult.arguments.find("name") != parserResult.arguments.end())
		defintion->setName(parserResult.arguments.at("name"));

	dao->updateDefinition(*defintion);
}

} // namespace Actions
