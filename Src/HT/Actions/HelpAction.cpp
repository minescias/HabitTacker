#include "HT/Actions/HelpAction.h"

#include <iostream>

namespace Actions
{

HelpAction::HelpAction()
{
}

void HelpAction::execute()
{
	std::cout <<
		"A simple habit tracker"
		"\n"
		"\n usage: ht <command> <arguments>"
		"\n"
		"\n Available commands:"
		"\n 	help - prints this message"
		"\n 	init - creates new database"
		"\n 	add <name> - adds new habit with given name"
		"\n 	<filer> done - sets habit as done for today"
		"\n 	list - list all habits"
		"\n"
	;
}

} // namespace actions

