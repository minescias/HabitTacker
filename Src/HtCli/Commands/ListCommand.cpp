#include "HtCli/Commands/ListCommand.h"

#include <iomanip>
#include <iostream>

#include "CLI/App.hpp"

namespace Commands
{
void ListCommand::execute()
{
	auto dao =
		daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
	auto habits = dao->getDefinitions();

	if (habits.empty())
	{
		std::cout << "No habits found, try to add some using 'htr add'\n";
		return;
	}

	printHeader();

	for (auto const& habit : habits)
	{
		std::cout << "\n"
				  << std::setw(4) << habit->getId() << " " << habit->getName();
	}

	std::cout << "\n";
}

void ListCommand::setCliParameters(CLI::App* app)
{
	app->add_subcommand("list", "Prints all habits");
}

void ListCommand::printHeader() const
{
	std::cout << "\nid   name"
				 "\n---- ----------------------------------------";
}

} // namespace Commands
