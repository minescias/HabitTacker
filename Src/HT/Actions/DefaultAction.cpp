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
	auto habitDefinitions = definitionDao->getDefinitions();
	auto habits = habitDao->getHabitsFromLastTwoWeeks(date);

	// if (habitId.empty())
	// 	throw ActionError ("No filter specified");

	prepareCompletionTable(habitDefinitions);
	fillCompletionTable(habits, date);

	printHeader(date);

	for(auto const& definition: habitDefinitions)
	{
		// to formatowanie tutaj jest tak straszne... Ale działa :)
		std::cout
			<< "\n" <<  std::setw (4) << definition->getId()
			<< " " << definition->getName()
			<< std::setw (40 - definition->getName().length()) << " "
			<< getCompletionString(definition->getId());
	}

	std::cout << "\n";
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

void DefaultAction::prepareCompletionTable(
	const std::vector<Entity::HabitDefinitionEntityPtr>& definitions)
{
	for(auto const& definition: definitions)
		completionTable.emplace(definition->getId(), std::vector<bool>(14, false));
}

void DefaultAction::fillCompletionTable(
	const std::vector<Entity::HabitEntityPtr>& habits, time_t date)
{
	const auto printedDays{14};
	const auto secondsInDay{86400}; // 86400 = 24 * 60 * 60

	for (auto const& habit: habits)
	{
		int daysBack = (date - habit->getDate())/secondsInDay;
		completionTable.at(habit->getHabitId())[printedDays - daysBack - 1] = true;
	}
}

std::string DefaultAction::getCompletionString(int habitId)
{
	std::string result;

	auto completion = completionTable.at(habitId);

	for (auto resultForDay: completion)
	{
		if (resultForDay == false)
			result += " __";
		else
			result += " XX";
	}

	return result;
}

} // namespace Actions