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
		"\n usage: htr <command> <arguments>"
		"\n"
		"\n Available commands:"
		"\n 	- prints completion table from last two weeks"
		"\n 	help - prints this message"
		"\n 	veriosn - prints program version"
		"\n 	init - creates new database"
		"\n 	add <name> - adds new habit with given name"
		"\n 	<habit_id> done - sets habit as done for today"
		"\n 	list - list all habits"
		"\n"
	;
}

} // namespace actions

