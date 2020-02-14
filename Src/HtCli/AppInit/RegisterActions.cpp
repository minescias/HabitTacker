#include "HtCli/AppInit/RegisterActions.h"

// #include "HtCli/Actions/AddAction.h"
// #include "HtCli/Actions/DefaultAction.h"
#include "HtCli/Actions/DoneAction.h"
#include "HtCli/Actions/EditAction.h"
// #include "HtCli/Actions/ListAction.h"

std::unique_ptr<Actions::ActionRegister> registerActions()
{
	auto actionRegister = std::make_unique<Actions::ActionRegister>();

	// actionRegister->reg("add", []()->std::unique_ptr<Actions::IAction>
	// 	{return std::make_unique<Actions::AddAction>();});

	// actionRegister->reg("", []()->std::unique_ptr<Actions::IAction>
	// 	{return std::make_unique<Actions::DefaultAction>();});

	actionRegister->reg("done", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<Actions::DoneAction>();});

	actionRegister->reg("edit", []()->std::unique_ptr<Actions::IAction>
		{return std::make_unique<Actions::EditAction>();});

	// actionRegister->reg("list", []()->std::unique_ptr<Actions::IAction>
	// 	{return std::make_unique<Actions::ListAction>();});

	return actionRegister;
}
