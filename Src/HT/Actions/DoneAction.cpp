#include "HT/Actions/DoneAction.h"

#include <Core/Cli/Validator.h>
#include "Core/DateTime/DateLiteral.h"
#include "Core/DateTime/DateTime.h"
#include "Core/DateTime/DateTimeGetter.h"

#include "HT/Actions/ActionError.h"

namespace Actions
{

DoneAction::DoneAction()
{
}

void DoneAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	definitionDao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");
}

void DoneAction::execute(const Cli::Parameters& parserResult)
{
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
			throw ActionError("Habit " + parserResult.getFilter() +
				" was already set for this day");
		}

		habitDao->saveHabit(habit);
	}
	else
	{
		habitDao->deleteHabit(habit);
	}
}

void DoneAction::validateParameters(const Cli::Parameters& parameters) const
{
	auto validator = Cli::Validator();
	validator.enableFilter();
	validator.addParam("date").type(Cli::ParamType::Date);
	validator.addParam("reset");
	validator.validate(parameters);

	auto habitId = parameters.getFilter();
	if (habitId.empty())
		throw ActionError ("No filter specified");

	auto definition = definitionDao->getDefinition(stoi(habitId));
	if (!definition)
		throw ActionError ("Habit " + habitId + " does not exist");

	auto date = getDate(parameters);
	if (date < definition->getBeginDate())
	{
		throw ActionError("Cannot set habit before it's begin date which is " +
			Dt::DateTime(definition->getBeginDate()).dateString());
	}

	if (date > Dt::getCurrentDate())
		throw ActionError("Cannot set habit in the future");
}

Dt::Timestamp DoneAction::getDate(const Cli::Parameters& parserResult) const
{
	if (!parserResult.getParameter("date").empty())
		return Dt::DateLiteral().parse(parserResult.getParameter("date"));

	return Dt::getCurrentDate();
}

} // namespace Actions
