#include "Core/Logger/Logger.h"

#include <iostream>

namespace Log
{

Logger::Logger()
{
}

void Logger::log(const std::string& message)
{
    std::cout << message;
}

} // namespace Log
