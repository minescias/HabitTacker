#include "HT/Actions/DefaultAction.h"

#include <iomanip>
#include <iostream>
#include <vector>

namespace Actions
{

DefaultAction::DefaultAction(
	Dao::IHabitDao* habitDao , Dao::IHabitDefinitionDao* definitionDao)
	:habitDao(habitDao), definitionDao(definitionDao)
{
}

void DefaultAction::execute(time_t date)
{
	auto habits = definitionDao->getDefinitions();

	printHeader(date);

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

void DefaultAction::printHeader(time_t date) const
{
	std::cout <<
		"\n  id name                                    "
			+ getWeekDaysHeaderEndingWithDate(date) +
		"\n---- ----------------------------------------"
			+ " -----------------------------------------"
	;
}

std::string DefaultAction::getWeekDaysHeaderEndingWithDate(time_t date) const
{
	std::string result;
	std::vector<std::string> weekDays{"Sa", "Mo", "Tu", "We", "Th", "Fr", "Su"};

	auto localDate = std::localtime(&date); // thread unsafe
	const auto firstDay = (localDate->tm_wday + 1) % 7;
	const auto daysToPrint{14};

	for (int i = firstDay; i < firstDay + daysToPrint; i++)
		result += " " + weekDays[i % 7];

	return result;
}

} // namespace Actions