#include "HtCli/Actions/DefaultAction.h"

#include <iomanip>
#include <iostream>

#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/ParseDate.h>

#include "HtCli/Actions/ActionError.h"

namespace Actions
{
// https://stackoverflow.com/questions/4063146/getting-the-actual-length-of-a-utf-8-encoded-stdstring
int getUtf8StringLength(const std::string& str)
{
	int len = 0;

	for (auto c : str)
		len += (c & 0xc0) != 0x80;

	return len;
}

DefaultAction::DefaultAction() : daysToPrint(14)
{
}

void DefaultAction::doExecute(const Cli::Parameters& parameters)
{
	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");
	definitionDao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	auto habitDefinitions = definitionDao->getDefinitions();

	Dt::Date date;
	if (parameters.getDefaultParameter().empty())
		date = Dt::getCurrentDate();
	else
		date = Dt::parseDate(parameters.getDefaultParameter());

	if (habitDefinitions.empty())
		throw ActionError("No habits found, try to add some using 'htr add'\n");

	prepareCompletionTable(date, habitDefinitions);
	fillCompletionTable(date);
	printHeader(date);

	for (auto const& definition : habitDefinitions)
	{
		// to formatowanie tutaj jest tak straszne... Ale działa :)
		std::cout << "\n"
				  << std::setw(4) << definition->getId() << " "
				  << definition->getName()
				  << std::setw(40 - getUtf8StringLength(definition->getName()))
				  << " " << getCompletionString(definition->getId());
	}

	std::cout << "\n";
}

void DefaultAction::initValidator()
{
	validator.addDefaultParameter()
		.type(Cli::ParamType::Date)
		.requirement(Cli::RequirementLevel::Optional);
}

void DefaultAction::printHeader(Dt::Date date) const
{
	std::cout << "\n  id name                                    "
			+ getWeekDaysHeaderEndingWithDate(date)
			+ "\n---- ----------------------------------------"
			+ " -----------------------------------------";
}

std::string DefaultAction::getWeekDaysHeaderEndingWithDate(Dt::Date date) const
{
	std::string result;
	std::vector<std::string> weekDays{"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
	const auto firstDay = 1;
	// const auto firstDay = (Dt::DateTime{date}.weekDay() + 1) % 7;
	// TODO: pobrać dzień tygodnia z Dt::Date

	for (int i = firstDay; i < firstDay + daysToPrint; i++)
		result += " " + weekDays[i % 7];

	return result;
}

void DefaultAction::prepareCompletionTable(
	Dt::Date date, const std::vector<Entity::HabitDefinitionEntityPtr>& definitions)
{
	for (auto const& definition : definitions)
	{
		auto id = definition->getId();
		completionTable.emplace(
			id, std::vector<CompletionType>(14, CompletionType::No));

		// TODO: Wygodna metoda do odejmowania dat

		auto daysBack =
			date::sys_days{date} - date::sys_days{definition->getBeginDate()};
		auto dayId = daysToPrint - daysBack.count() - 1;

		if (dayId >= 0)
		{
			for (int i = 0; i < dayId; i++)
				completionTable.at(id)[i] = CompletionType::None;
		}
	}
}
void DefaultAction::fillCompletionTable(Dt::Date date)
{
	auto habits = habitDao->getHabitsFromLastTwoWeeks(date);

	for (auto const& habit : habits)
	{
		auto daysBack = date::sys_days{date} - date::sys_days{habit->getDate()};
		auto dayId = daysToPrint - daysBack.count() - 1;
		completionTable.at(habit->getHabitId())[dayId] = CompletionType::Yes;
	}
}

std::string DefaultAction::getCompletionString(int habitId)
{
	std::string result;

	auto completion = completionTable.at(habitId);

	for (auto resultForDay : completion)
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
