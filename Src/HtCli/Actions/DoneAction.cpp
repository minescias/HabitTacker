#include "HtCli/Actions/DoneAction.h"

#include <Core/DateTime/DateLiteral.h>
#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/FormatDate.h>

#include "HtCli/Actions/ActionError.h"

namespace Actions
{
void DoneAction::doExecute(const Cli::Parameters& parserResult)
{
	definitionDao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");

	validateParameters(parserResult);

	auto reset = parserResult.getFlag("reset");

	auto definitionId = stoi(parserResult.getFilter());
	auto habit = Entity::HabitEntity();
	habit.setHabitId(definitionId);
	habit.setDate(getDate(parserResult));

	if (!reset)
	{
		if (habitDao->checkIfHabitIsSetForDay(habit))
		{
			throw ActionError(
				"Habit " + parserResult.getFilter()
				+ " was already set for this day");
		}

		habitDao->saveHabit(habit);
	}
	else
	{
		habitDao->deleteHabit(habit);
	}
}

void DoneAction::initValidator()
{
	validator.addFilter().requirement(Cli::RequirementLevel::Required);
	validator.addParam("date").type(Cli::ParamType::Date);
	validator.addParam("reset");
	validator.addFilter().requirement(Cli::RequirementLevel::Required);
}

void DoneAction::validateParameters(const Cli::Parameters& parameters) const
{
	auto habitId = parameters.getFilter();

	auto definition = definitionDao->getDefinition(stoi(habitId));
	if (!definition)
		throw ActionError("Habit " + habitId + " does not exist");

	auto date = getDate(parameters);
	if (date < definition->getBeginDate())
	{
		throw ActionError(
			"Cannot set habit before it's begin date which is "
			+ Dt::formatDate(definition->getBeginDate()));
	}

	if (date > Dt::getCurrentDate())
		throw ActionError("Cannot set habit in the future");
}

Dt::Date DoneAction::getDate(const Cli::Parameters& parserResult) const
{
	if (!parserResult.getParameter("date").empty())
		return Dt::DateLiteral().parse(parserResult.getParameter("date"));

	return Dt::getCurrentDate();
}

} // namespace Actions
