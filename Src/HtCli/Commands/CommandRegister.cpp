#include "HtCli/Commands/CommandRegister.h"

#include <string>

#include "CLI/App.hpp"
#include "Core/Exceptions/RuntimeError.h"

#include "HtCli/Commands/ICommand.h"

namespace Commands
{
CommandRegister::CommandRegister(CLI::App* app) : app(app)
{
}

void CommandRegister::reg(const std::string& name, ICommandPtr command)
{
	if (commandsMap.find(name) != commandsMap.end())
		throw LogicError("Redefinition of '" + name + "' action");

	command->setCliParameters(app);
	commandsMap[name] = std::move(command);
}

ICommand* CommandRegister::get(const std::string& name)
{
	if (commandsMap.find(name) == commandsMap.end())
		throw RuntimeError("Action '" + name + "' is not registered");

	return commandsMap.at(name).get();
}

CommandRegister::CommandsMap& CommandRegister::getAllCommands()
{
	return commandsMap;
}

} // namespace Commands
