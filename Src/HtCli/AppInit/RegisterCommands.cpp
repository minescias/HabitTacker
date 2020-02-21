#include "HtCli/AppInit/RegisterCommands.h"

#include "HtCli/Actions/AddAction.h"
#include "HtCli/Actions/DefaultAction.h"
#include "HtCli/Actions/DoneAction.h"
#include "HtCli/Actions/EditAction.h"
#include "HtCli/Actions/InitAction.h"
#include "HtCli/Actions/ListAction.h"

std::unique_ptr<Commands::CommandRegister> registerCommands(CLI::App* app)
{
	auto commandRegister = std::make_unique<Commands::CommandRegister>(app);

	commandRegister->reg("add", std::make_unique<Commands::AddCommand>());
	commandRegister->reg("show", std::make_unique<Commands::ShowCommand>());
	commandRegister->reg("done", std::make_unique<Commands::DoneCommand>());
	commandRegister->reg("list", std::make_unique<Commands::ListCommand>());
	commandRegister->reg("edit", std::make_unique<Commands::EditCommand>());
	commandRegister->reg("init", std::make_unique<Commands::InitCommand>());

	return commandRegister;
}
