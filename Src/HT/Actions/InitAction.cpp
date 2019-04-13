#include "HT/Actions/InitAction.h"

#include <iostream>

namespace Actions
{

InitAction::InitAction()
{
}

void InitAction::execute()
{
	std::cout << "InitAction::execute()\n";
}

} // namespace Actions
