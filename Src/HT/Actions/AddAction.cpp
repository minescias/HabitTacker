#include <HT/Actions/AddAction.h>

#include <HT/Actions/ActionError.h>
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

void AddAction::initValidator()
{
	validator
		.addDefaultParameter()
		.requirement(Cli::RequirementLevel::Required)
		.errorMessage("No habit name specified");
}

void AddAction::doExecute(const Cli::Parameters& parameters)
{
	auto dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	auto name = parameters.getDefaultParameter();
	auto existingDefinition = dao->getDefinition(name);

	if (existingDefinition)
		throw ActionError("Habit with name '" + name + "' already exists");

	auto newDefinition = Entity::HabitDefinitionEntity();
	newDefinition.setName(name);
	dao->saveDefinition(newDefinition);
}

} // namespace Actions


