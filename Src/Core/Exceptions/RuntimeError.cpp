#include "Core/Exceptions/RuntimeError.h"

#include "Core/Logger/Log.h"

RuntimeError::RuntimeError(const std::string& message)
	: std::runtime_error(message)
{
	log(Log::Levels::Error, "RuntimeError: " + message);
}
