#ifndef __ACTION_ERROR
#define __ACTION_ERROR

#include "Core/Exceptions/RuntimeError.h"

namespace Actions
{

class ActionError : public RuntimeError
{
public:
	ActionError(const std::string& message);
};

} // namespace Actions

#endif
