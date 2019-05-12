#include "HT/Actions/DoneAction.h"

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
	auto habitId = parserResult.filter;
	if (habitId.empty())
		throw ActionError ("No filter specified");

	auto definitionId = stoi(habitId);
	if (!definitionDao->getDefinition(definitionId))
		throw ActionError ("Habit " + habitId + " does not exist");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(definitionId);
	habit.setDate(Dt::getCurrentDate());

	if (habitDao->checkIfHabitIsSetForDay(habit))
		throw ActionError("Habit " + habitId + " was already set for this day");

	habitDao->saveHabit(habit);
}

} // namespace Actions
