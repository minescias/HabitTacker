#include "HtCli/Commands/ShowCommand.h"

#include <iomanip>
#include <iostream>

#include "CLI/App.hpp"

#include "Core/DateTime/DateTimeGetter.h"
#include "Core/DateTime/Operators.h"
#include "Core/DateTime/ParseDate.h"

#include "HtCli/Commands/CommandError.h"

namespace
{
using date::days;
using date::sys_days;
} // namespace

namespace Commands
{
// https://stackoverflow.com/questions/4063146/getting-the-actual-length-of-a-utf-8-encoded-stdstring
int getUtf8StringLength(const std::string& str)
{
	int len = 0;

	for (auto c : str)
		len += (c & 0xc0) != 0x80;

	return len;
}

ShowCommand::ShowCommand() : daysToPrint(14)
{
}

void ShowCommand::setCliParameters(CLI::App* app)
{
	auto command = app->add_subcommand("show");
	command->add_option("-d,--date", dateStr, "Show results to this date");
}

void ShowCommand::execute()
{
	if (dateStr.empty())
		date = Dt::getCurrentDate();
	else
		date = Dt::parseDate(dateStr);

	habitDao = daoFactory->createDao<Dao::IHabitDao>("habit");
	definitionDao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

	auto habitDefinitions = definitionDao->getDefinitions();

	if (habitDefinitions.empty())
	{
		throw CommandError(
			"No habits found, try to add some using 'htr add'\n");
	}

	table.addColumn("Id");
	table.addColumn("Name");
	addWeekdayColumns(date);

	for (auto const& definition : habitDefinitions)
	{
		table.addLine();
		table.setValue("Id", std::to_string(definition->getId()));
		table.setValue("Name", definition->getName());
		initWeekdayValues(*definition, date);
		fillWeekdayValues(*definition, date);
	}

	table.print();
}

void ShowCommand::addWeekdayColumns(Dt::Date date)
{
	std::string result;
	std::vector<std::string> weekDays{"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
	const auto firstDay = 1;
	// const auto firstDay = (Dt::DateTime{date}.weekDay() + 1) % 7;
	// TODO: pobrać dzień tygodnia z Dt::Date

	for (int i = firstDay; i < firstDay + daysToPrint; i++)
		table.addColumn("wd_" + std::to_string(i), weekDays[i % 7]);
}

void ShowCommand::initWeekdayValues(
	Entity::HabitDefinitionEntity& definition, Dt::Date date)
{
	auto firstColumnId = table.getColumnIndex("wd_1");
	auto beginDateId = sys_days{date} - sys_days{definition.getBeginDate()};

	for (int i = 0; i < daysToPrint; i++)
	{
		if ((beginDateId.count() - daysToPrint + i + 2) > 0)
			table.setValue(firstColumnId + i, "__");
	}
}

void ShowCommand::fillWeekdayValues(
	Entity::HabitDefinitionEntity& definition, Dt::Date date)
{
	auto firstColumnId = table.getColumnIndex("wd_1");

	auto habits =
		habitDao->getHabits(definition.getId(), date - days{daysToPrint}, date);

	for (const auto& habit : habits)
	{
		auto columnId = firstColumnId - 1
			+ (sys_days{habit->getDate()} - sys_days{date}).count() + daysToPrint;

		table.setValue(columnId, "XX");
	}
}

} // namespace Commands
