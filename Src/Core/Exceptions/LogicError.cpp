#include "Core/Exceptions/LogicError.h"

#include "Core/Logger/Log.h"

LogicError::LogicError(const std::string& message)
    : std::logic_error(message)
{
    log(Log::Levels::Error, "LogicError: " + message);
}

