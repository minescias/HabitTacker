#include "HT/Actions/DefaultAction.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include "HT/Actions/ActionError.h"

namespace Actions
{

DefaultAction::DefaultAction()
{
}

void DefaultAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");
	definitionDao= daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
}

void DefaultAction::execute(time_t date)
{
	auto habitDefinitions = definitionDao->getDefinitions();

	if (habitDefinitions.empty())
		throw ActionError ("No habits found, try to add some using 'ht add'\n");

	prepareCompletionTable(habitDefinitions);
	fillCompletionTable(date);
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

void DefaultAction::fillCompletionTable(time_t date)
{
	const auto printedDays{14};
	const auto secondsInDay{86400}; // 86400 = 24 * 60 * 60

	auto habits = habitDao->getHabitsFromLastTwoWeeks(date);

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
