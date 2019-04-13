#include "Core/Utils/Exceptions/LogicError.h"

#include "Core/Utils/Logger/Log.h"

LogicError::LogicError(const std::string& message)
    : std::logic_error(message)
{
    log(message);
}

