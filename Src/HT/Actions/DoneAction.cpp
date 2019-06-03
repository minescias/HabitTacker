#include "HT/Actions/DoneAction.h"

#include "Core/DateTime/DateLiteral.h"
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
	auto reset = parserResult.arguments.find("reset")
		!= parserResult.arguments.end();

	auto habitId = parserResult.filter;
	if (habitId.empty())
		throw ActionError ("No filter specified");

	auto definitionId = stoi(habitId);
	if (!definitionDao->getDefinition(definitionId))
		throw ActionError ("Habit " + habitId + " does not exist");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(definitionId);
	habit.setDate(getDate(parserResult));

	if (!reset)
	{
		if (habitDao->checkIfHabitIsSetForDay(habit))
			throw ActionError("Habit " + habitId + " was already set for this day");

		habitDao->saveHabit(habit);
	}
	else
	{
		habitDao->deleteHabit(habit);
	}
}

Dt::Timestamp DoneAction::getDate(const Cli::ParserResult& parserResult) const
{
	if (parserResult.arguments.find("date") != parserResult.arguments.end())
		return Dt::DateLiteral().parse(parserResult.arguments.at("date"));

	return Dt::getCurrentDate();
}

} // namespace Actions
