#include "HtCli/Commands/DoneCommand.h"

#include <string>

#include "CLI/App.hpp"
#include "fmt/core.h"

#include "Core/DateTime/DateLiteral.h"
#include "Core/DateTime/DateTimeGetter.h"
#include "Core/DateTime/FormatDate.h"

#include "HtCli/Commands/CommandError.h"

namespace Commands
{
void DoneCommand::setCliParameters(CLI::App* app)
{
	auto command = app->add_subcommand("done", "Set habit as done for today");
	command->add_option("-i,--habit_id", habitId, "Id of changed habit")->required();
	command->add_option("-d,--date", dateStr, "Date");

	command->add_option(
		"-r,--result",
		result,
		"Result for current day, "
		"Set to current target by default");

	command->add_flag("--reset", reset, "Reset daily progress")
		->excludes("--result")
		->default_val(false);
}

void DoneCommand::execute()
{
	definitionDao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	validateParameters();

	requirementDao = daoFactory->createDao<Dao::IRequirementDao>("requirement");
	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(habitId);
	habit.setDate(getDate());

	if (reset)
	{
		habitDao->deleteHabit(habit);
		return;
	}

	if (habitDao->checkIfHabitIsSetForDay(habit))
	{
		throw CommandError(
			"Habit " + std::to_string(habitId)
			+ " was already set for this day");
	}

	habit.setResult(getResult());
	habitDao->saveHabit(habit);
}

void DoneCommand::validateParameters() const
{
	auto definition = definitionDao->getDefinition(habitId);

	if (!definition)
		throw CommandError(fmt::format("Habit {0} does not exist", habitId));

	auto date = getDate();
	if (date < definition->getBeginDate())
	{
		throw CommandError(
			"Cannot set habit before it's begin date which is "
			+ Dt::formatDate(definition->getBeginDate()));
	}

	if (date > Dt::getCurrentDate())
		throw CommandError("Cannot set habit in the future");
}

Dt::Date DoneCommand::getDate() const
{
	if (dateStr.empty())
		return Dt::getCurrentDate();

	return Dt::DateLiteral().parse(dateStr);
}

int DoneCommand::getResult() const
{
	if (!result)
		return requirementDao->getCurrentTarget(habitId);
	else
		return *result;
}

} // namespace Commands
