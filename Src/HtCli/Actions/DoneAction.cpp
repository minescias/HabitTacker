#include "HtCli/Actions/DoneAction.h"

#include <Core/DateTime/DateLiteral.h>
#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/FormatDate.h>

#include "HtCli/Actions/ActionError.h"

namespace Actions
{
void DoneAction::initValidator()
{
	validator.addFilter().requirement(Cli::RequirementLevel::Required);
	validator.addDefaultParameter().type(Cli::ParamType::Integer);
	validator.addParam("date").type(Cli::ParamType::Date);
	validator.addParam("reset");
}

void DoneAction::doExecute(const Cli::Parameters& parameters)
{
	definitionDao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	validateParameters(parameters);

	requirementDao = daoFactory->createDao<Dao::IRequirementDao>("requirement");
	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");

	auto reset = parameters.getFlag("reset");
	auto definitionId = stoi(parameters.getFilter());
	auto habit = Entity::HabitEntity();
	habit.setHabitId(definitionId);
	habit.setDate(getDate(parameters));

	if (!reset)
	{
		if (habitDao->checkIfHabitIsSetForDay(habit))
		{
			throw ActionError(
				"Habit " + parameters.getFilter()
				+ " was already set for this day");
		}

		habit.setResult(getResult(parameters, definitionId));
		habitDao->saveHabit(habit);
	}
	else
	{
		habitDao->deleteHabit(habit);
	}
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

Dt::Date DoneAction::getDate(const Cli::Parameters& parameters) const
{
	if (!parameters.getParameter("date").empty())
		return Dt::DateLiteral().parse(parameters.getParameter("date"));

	return Dt::getCurrentDate();
}

int DoneAction::getResult(const Cli::Parameters& parameters, int definitionId) const
{
	auto result = parameters.getDefaultParameter();
	if (result.empty())
		return requirementDao->getCurrentTarget(definitionId);
	else
		return stoi(result);
}

} // namespace Actions
