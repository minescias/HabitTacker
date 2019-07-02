#include "Core/Utils/Exceptions/RuntimeError.h"

RuntimeError::RuntimeError(const std::string& message)
    : std::runtime_error(message)
{
}
