#include "HT/Actions/ActionRegister.h"

#include <string>

namespace Actions
{

ActionRegister::ActionRegister()
{
}

void ActionRegister::reg(const std::string& name, ActionCreatorFunc creator)
{
	if (creatorsMap.find(name) != creatorsMap.end())
		throw LogicError("Redefinition of '" + name + "' action");

	creatorsMap[name] = creator;
}

std::unique_ptr<IAction> ActionRegister::get(const std::string& name)
{
	if (creatorsMap.find(name) == creatorsMap.end())
		throw LogicError("Action '" + name + "' is not registered");

	return creatorsMap.at(name)();
}

} // namespace Actions
