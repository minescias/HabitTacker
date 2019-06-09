#include "HT/Actions/DoneAction.h"

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

void DoneAction::execute(const Cli::ParserResult& parserResult)
{
	validateParameters(parserResult);

	auto reset = parserResult.arguments.find("reset")
		!= parserResult.arguments.end();

	auto definitionId = stoi(parserResult.filter);
	auto habit = Entity::HabitEntity();
	habit.setHabitId(definitionId);
	habit.setDate(getDate(parserResult));

	if (!reset)
	{
		if (habitDao->checkIfHabitIsSetForDay(habit))
		{
			throw ActionError("Habit " + parserResult.filter +
				" was already set for this day");
		}

		habitDao->saveHabit(habit);
	}
	else
	{
		habitDao->deleteHabit(habit);
	}
}

void DoneAction::validateParameters(const Cli::ParserResult& parserResult) const
{
	auto habitId = parserResult.filter;
	if (habitId.empty())
		throw ActionError ("No filter specified");

	auto definition = definitionDao->getDefinition(stoi(habitId));
	if (!definition)
		throw ActionError ("Habit " + habitId + " does not exist");

	auto date = getDate(parserResult);
	if (date < definition->getBeginDate())
	{
		throw ActionError("Cannot set habit before it's begin date which is " +
			Dt::DateTime(definition->getBeginDate()).dateString());
	}

	if (date > Dt::getCurrentDate())
		throw ActionError("Cannot set habit in the future");
}

Dt::Timestamp DoneAction::getDate(const Cli::ParserResult& parserResult) const
{
	if (parserResult.arguments.find("date") != parserResult.arguments.end())
		return Dt::DateLiteral().parse(parserResult.arguments.at("date"));

	return Dt::getCurrentDate();
}

} // namespace Actions
