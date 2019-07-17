#include "Core/Utils/Exceptions/LogicError.h"

#include "Core/Logger/Log.h"

LogicError::LogicError(const std::string& message)
    : std::logic_error(message)
{
    log("LogicError: " + message, Log::Levels::Error);
}

