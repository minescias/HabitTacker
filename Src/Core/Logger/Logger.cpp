#include "Core/Logger/Logger.h"

#include <iostream>

namespace Log
{

Logger::Logger(bool enabled)
    : enabled(enabled)
{
    std::cout << "Init";

}

void Logger::log(const std::string& message)
{
   // if (enabled)
        std::cout << message;
}

} // namespace Log
