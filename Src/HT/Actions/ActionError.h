#ifndef __ACTION_ERROR
#define __ACTION_ERROR

#include "Core/Utils/Exceptions/RuntimeError.h"

class ActionError : public RuntimeError
{
public:
	ActionError(const std::string& message);
};

#endif
