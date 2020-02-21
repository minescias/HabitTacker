#include "HtCli/AppInit/RegisterCommands.h"

#include "HtCli/Commands/AddCommand.h"
#include "HtCli/Commands/DoneCommand.h"
#include "HtCli/Commands/EditCommand.h"
#include "HtCli/Commands/InitCommand.h"
#include "HtCli/Commands/ListCommand.h"
#include "HtCli/Commands/ShowCommand.h"

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
