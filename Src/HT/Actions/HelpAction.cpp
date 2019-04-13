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
		"\n"
	;
}

} // namespace actions

