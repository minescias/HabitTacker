#include "HT/Actions/DefaultAction.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include <Core/DateTime/DateTime.h>
#include <Core/DateTime/DateTimeGetter.h>

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

void DefaultAction::execute(const Cli::ParserResult& parserResult)
{
	auto habitDefinitions = definitionDao->getDefinitions();

	Dt::Timestamp date;
	if (parserResult.argument.empty())
		date = Dt::getCurrentDate();
	else
		date = Dt::DateTime{parserResult.argument}.unixTime();

	if (habitDefinitions.empty())
		throw ActionError ("No habits found, try to add some using 'htr add'\n");

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

void DefaultAction::printHeader(Dt::Timestamp date) const
{
	std::cout <<
		"\n  id name                                    "
			+ getWeekDaysHeaderEndingWithDate(date) +
		"\n---- ----------------------------------------"
			+ " -----------------------------------------"
	;
}

std::string DefaultAction::getWeekDaysHeaderEndingWithDate(Dt::Timestamp date) const
{
	std::string result;
	std::vector<std::string> weekDays{"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

	const auto firstDay = (Dt::DateTime{date}.weekDay() + 1) % 7;
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

void DefaultAction::fillCompletionTable(Dt::Timestamp date)
{
	const auto printedDays{14};
	auto habits = habitDao->getHabitsFromLastTwoWeeks(date);

	for (auto const& habit: habits)
	{
		auto daysBack = Dt::Duration{date - habit->getDate()}.getDays();
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
