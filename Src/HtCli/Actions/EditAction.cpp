#include "HtCli/Actions/EditAction.h"

#include "CLI/App.hpp"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HtCli/Actions/ActionError.h"
#include "fmt/core.h"

namespace Commands
{
void EditCommand::setCliParameters(CLI::App* app)
{
	auto command = app->add_subcommand("edit", "Edit habit definition");
	command->add_option("-i,--habit_id", habitId, "Id of edited definition")->required();
	command->add_option("-n,--name", name, "New name");
}

void EditCommand::execute()
{
	auto dao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	if (name.empty())
		throw Actions::ActionError("Nothing to change");

	auto defintion = dao->getDefinition(habitId);
	if (!defintion)
		throw Actions::ActionError(
			fmt::format("Habit with id = {0} does not exist", habitId));

	defintion->setName(name);
	dao->updateDefinition(*defintion);
}

// void EditAction::doExecute(const Cli::Parameters& parameters)
// {
// 	auto dao =
// 		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
// 	auto habitId = parameters.getFilter();

// 	auto name = parameters.getParameter("name");
// 	if (name.empty())
// 		throw ActionError("Nothing to change");

// 	auto defintion = dao->getDefinition(std::stoi(habitId));
// 	if (!defintion)
// 		throw ActionError("Habit with id = " + habitId + " does not exist");

// 	defintion->setName(name);
// 	dao->updateDefinition(*defintion);
// }

// void EditAction::initValidator()
// {
// 	validator.addFilter().requirement(Cli::RequirementLevel::Required);
// 	validator.addParam("name").type(Cli::ParamType::String);
// }

} // namespace Commands
