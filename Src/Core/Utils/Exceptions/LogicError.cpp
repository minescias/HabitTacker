#include "Core/Utils/Exceptions/LogicError.h"

LogicError::LogicError(const std::string& message)
    : std::logic_error(message)
{
}

