#include "HtCli/Commands/EditCommand.h"

#include "CLI/App.hpp"
#include "fmt/core.h"

#include "HT/Dao/HabitDefinitionDao.h"
#include "HtCli/Commands/CommandError.h"

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
		throw CommandError("Nothing to change");

	auto defintion = dao->getDefinition(habitId);
	if (!defintion)
		throw CommandError(
			fmt::format("Habit with id = {0} does not exist", habitId));

	defintion->setName(name);
	dao->updateDefinition(*defintion);
}

} // namespace Commands
