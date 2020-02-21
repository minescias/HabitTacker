#include <HtCli/Commands/CommandError.h>

namespace Commands
{
CommandError::CommandError(const std::string& message) : RuntimeError(message)
{
}

} // namespace Commands
