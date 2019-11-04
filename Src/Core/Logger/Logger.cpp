#include "Core/Logger/Logger.h"

#include <iostream>

namespace Log
{
Logger::Logger(std::unique_ptr<Config> config) : config(std::move(config))
{
}

void Logger::log(Levels level, const std::string& message)
{
	if (isLogEnabled(level))
		std::cout << message;
}

bool Logger::isLogEnabled(Levels level)
{
	return config->enabled && config->levels.find(level) != config->levels.end();
}

} // namespace Log
