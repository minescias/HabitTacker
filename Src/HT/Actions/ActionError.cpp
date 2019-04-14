#include <HT/Actions/ActionError.h>

ActionError::ActionError(const std::string& message)
	: RuntimeError(message)
{
}
