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

	if (name.empty())
		throw ActionError("No habit name specified");

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
	Cli::Validator().validate(parameters); 
}

} // namespace Actions


