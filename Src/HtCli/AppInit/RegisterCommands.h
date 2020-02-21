#ifndef __REGISTER_COMMANDS_H
#define __REGISTER_COMMANDS_H

#include <HtCli/Commands/CommandRegister.h>

namespace CLI
{
class App;

} // namespace CLI

std::unique_ptr<Commands::CommandRegister> registerCommands(CLI::App* app);

#endif // __REGISTER_ACTIONS_H
