#include <HT/Actions/ActionError.h>

namespace Actions
{

ActionError::ActionError(const std::string& message)
	: RuntimeError(message)
{
}

} // namespace Actions
