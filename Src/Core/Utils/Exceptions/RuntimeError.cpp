#include "Core/Utils/Exceptions/RuntimeError.h"

#include "Core/Utils/Logger/Log.h"

RuntimeError::RuntimeError(const std::string& message)
    : std::runtime_error(message)
{
    log(message);
}


