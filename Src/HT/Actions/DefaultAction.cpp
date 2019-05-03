#include "HT/Actions/DefaultAction.h"

#include <iomanip>
#include <iostream>

namespace Actions
{

DefaultAction::DefaultAction(
	Dao::IHabitDao* habitDao , Dao::IHabitDefinitionDao* definitionDao)
	:habitDao(habitDao), definitionDao(definitionDao)
{
}

void DefaultAction::execute()
{
	auto habits = definitionDao->getDefinitions();

	printHeader();

	for(auto const& habit: habits)
	{
		std::cout
			<< "\n" <<  std::setw (4) << habit->getId()
			<< " " << habit->getName();
	}

	std::cout << "\n";

	// if (habitId.empty())
	// 	throw ActionError ("No filter specified");

	// auto definitionId = stoi(habitId);
	// if (!definitionDao->getDefinition(definitionId))
	// 	throw ActionError ("Habit " + habitId + " does not exist");

	// auto today = time(nullptr);
	// today -= (today % 86400); // 86400 = 24 * 60 * 60

	// auto habit = Entity::HabitEntity();
	// habit.setHabitId(definitionId);
	// habit.setDate(today);

	// if (habitDao->checkIfHabitIsSetForDay(habit))
	// 	throw ActionError("Habit " + habitId + " was already set for this day");

	// habitDao->saveHabit(habit);
}

void DefaultAction::printHeader() const
{
	std::cout <<
		"\nid   name"
		"\n---- ----------------------------------------"
	;
}


} // namespace Actions