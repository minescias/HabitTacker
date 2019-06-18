#include "HT/Actions/ListAction.h"

#include <iomanip>
#include <iostream>

namespace Actions
{

ListAction::ListAction()
{

}

void ListAction::setDaoFactory(Dao::DaoFactory* factory)
{
	// dao = factory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
}

void ListAction::execute(const Cli::ParserResult& parserResult)
{
	auto habits = dao->getDefinitions();

	if (habits.empty())
	{
		std::cout << "No habits found, try to add some using 'htr add'\n";
		return;
	}

	printHeader();

	for(auto const& habit: habits)
	{
		std::cout
			<< "\n" <<  std::setw (4) << habit->getId()
			<< " " << habit->getName();
	}

	std::cout << "\n";

}

void ListAction::printHeader() const
{
	std::cout <<
		"\nid   name"
		"\n---- ----------------------------------------"
	;
}

} // namespace Actions
