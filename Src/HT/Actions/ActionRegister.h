#ifndef __ACTION_REGISTER_H
#define __ACTION_REGISTER_H

#include <functional>

#include "HT/Actions/IAction.h"

namespace Actions
{

using ActionCreatorFunc = std::function<std::unique_ptr<IAction>()>;

class ActionRegister
{
public:
	ActionRegister();
	void reg(const std::string& name, ActionCreatorFunc creator);
	std::unique_ptr<IAction> get(const std::string& name);

private:
	std::map<std::string, ActionCreatorFunc> creatorsMap;
};

} // namespace Actions

#endif // __ACTION_REGISTER_H
