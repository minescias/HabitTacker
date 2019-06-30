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
	: daysToPrint(14)
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
	if (parserResult.getDefaultParameter().empty())
		date = Dt::getCurrentDate();
	else
		date = Dt::DateTime{parserResult.getDefaultParameter()}.unixTime();

	if (habitDefinitions.empty())
		throw ActionError ("No habits found, try to add some using 'htr add'\n");

	prepareCompletionTable(date, habitDefinitions);
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

	for (int i = firstDay; i < firstDay + daysToPrint; i++)
		result += " " + weekDays[i % 7];

	return result;
}

void DefaultAction::prepareCompletionTable(Dt::Timestamp date,
	const std::vector<Entity::HabitDefinitionEntityPtr>& definitions)
{
	for(auto const& definition: definitions)
	{
		auto id = definition->getId();
		completionTable.emplace(id, std::vector<CompletionType>(14, CompletionType::No));

		auto daysBack = Dt::Duration{date - definition->getBeginDate()}.getDays();
		auto dayId = daysToPrint - daysBack - 1;

		if (dayId >= 0)
		{
			for (int i = 0; i < dayId; i++)
				completionTable.at(id)[i] = CompletionType::None;
		}
	}
}

void DefaultAction::fillCompletionTable(Dt::Timestamp date)
{
	auto habits = habitDao->getHabitsFromLastTwoWeeks(date);

	for (auto const& habit: habits)
	{
		auto daysBack = Dt::Duration{date - habit->getDate()}.getDays();
		auto dayId = daysToPrint - daysBack - 1;
		completionTable.at(habit->getHabitId())[dayId] = CompletionType::Yes;
	}
}

std::string DefaultAction::getCompletionString(int habitId)
{
	std::string result;

	auto completion = completionTable.at(habitId);

	for (auto resultForDay: completion)
	{
		if (resultForDay == CompletionType::No)
			result += " __";
		else if (resultForDay == CompletionType::Yes)
			result += " XX";
		else
			result += "   ";
	}

	return result;
}

} // namespace Actions
