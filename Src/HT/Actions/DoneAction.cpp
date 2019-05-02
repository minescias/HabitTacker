#include "HT/Actions/DoneAction.h"

#include "HT/Actions/ActionError.h"

namespace Actions
{

DoneAction::DoneAction(
	Dao::IHabitDao* habitDao , Dao::IHabitDefinitionDao* definitionDao)
	:habitDao(habitDao), definitionDao(definitionDao)
{

}

void DoneAction::execute(const std::string& habitId)
{
	if (habitId.empty())
		throw ActionError ("No filter specified");

	auto definitionId = stoi(habitId);
	if (!definitionDao->getDefinition(definitionId))
		throw ActionError ("Habit " + habitId + " does not exist");

	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto habit = Entity::HabitEntity();
	habit.setHabitId(definitionId);
	habit.setDate(today);

	if (habitDao->checkIfHabitIsSetForDay(habit))
		throw ActionError("Habit " + habitId + " was already set for this day");

	habitDao->saveHabit(habit);
}

} // namespace Actions
