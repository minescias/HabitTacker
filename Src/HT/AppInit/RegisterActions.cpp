#include "HT/AppInit/RegisterActions.h"

#include "HT/Actions/AddAction.h"
#include "HT/Actions/DefaultAction.h"
#include "HT/Actions/DoneAction.h"
#include "HT/Actions/ListAction.h"

std::unique_ptr<Actions::ActionRegister> registerActions()
{
	auto actionRegister = std::make_unique<Actions::ActionRegister>();

	actionRegister->reg("add", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<Actions::AddAction>();});

	actionRegister->reg("", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<Actions::DefaultAction>();});

	actionRegister->reg("done", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<Actions::DoneAction>();});

	actionRegister->reg("list", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<Actions::ListAction>();});

	return actionRegister;
}
