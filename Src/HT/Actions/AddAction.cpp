#include <HT/Actions/AddAction.h>

#include <Core/Cli/Validator.h>
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

void AddAction::execute(const Cli::Parameters& parameters)
{
	validateParameters(parameters);
	auto name = parameters.getDefaultParameter();
	auto existingDefinition = dao->getDefinition(name);

	if (existingDefinition)
		throw ActionError("Habit with name '" + name + "' already exists");

	auto newDefinition = Entity::HabitDefinitionEntity();
	newDefinition.setName(name);
	dao->saveDefinition(newDefinition);
}

void AddAction::validateParameters(const Cli::Parameters& parameters)
{
	// korzystamy tylko z parametru domyślnego, stąd brak ustawień walidatora
	auto validator = Cli::Validator();
	validator
		.addDefaultParameter()
		.requirement(Cli::RequirementLevel::Required)
		.errorMessage("No habit name specified");

	validator.validate(parameters);
}

} // namespace Actions


