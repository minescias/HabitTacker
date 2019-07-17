#include "Core/Logger/Logger.h"

#include <iostream>

namespace Log
{

Logger::Logger(std::unique_ptr<Config> config)
    : config(std::move(config))
{
    std::cout << "Init";
}

void Logger::log(const std::string& message, Levels level)
{
    if (isLogEnabled(level))
        std::cout << message;
}

bool Logger::isLogEnabled(Levels level)
{
    return config->enabled 
        && config->levels.find(level) != config->levels.end();
}

} // namespace Log
