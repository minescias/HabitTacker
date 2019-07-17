#include "Core/Utils/Exceptions/RuntimeError.h"

#include "Core/Logger/Log.h"

RuntimeError::RuntimeError(const std::string& message)
    : std::runtime_error(message)
{
    log("RuntimeError: " + message, Log::Levels::Error);
}
