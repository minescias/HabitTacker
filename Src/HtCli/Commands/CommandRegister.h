#ifndef __COMMAND_REGISTER_H
#define __COMMAND_REGISTER_H

#include <memory>

#include "CLI/App.hpp"

#include "HtCli/Commands/ICommand.h"

namespace Commands
{
class CommandRegister
{
	using CommandsMap = std::map<std::string, std::unique_ptr<ICommand>>;
	using ICommandPtr = std::unique_ptr<ICommand>;

public:
	CommandRegister(CLI::App* app);

	void reg(const std::string& name, std::unique_ptr<ICommand> command);
	ICommand* get(const std::string& name);
	CommandsMap& getAllCommands();

private:
	CommandsMap commandsMap;
	CLI::App* app;
};

} // namespace Commands

#endif // __ACTION_REGISTER_H
