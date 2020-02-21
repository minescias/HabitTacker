#ifndef __ACTION_ERROR
#define __ACTION_ERROR

#include "Core/Exceptions/RuntimeError.h"

namespace Commands
{
class CommandError : public RuntimeError
{
public:
	CommandError(const std::string& message);
};

} // namespace Commands

#endif
