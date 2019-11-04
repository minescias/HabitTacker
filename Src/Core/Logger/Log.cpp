#include "Core/Logger/Log.h"
#include "Core/Logger/Logger.h"

namespace
{

Log::Logger* logger;

}

namespace Log
{

void setLogger(Log::Logger* newLogger)
{
	logger = newLogger;
}

} // namespace Log

void log(const std::string& message)
{
	if (!logger)
		return;

	logger->log(Log::Levels::Common, message + "\n");
}

void log(Log::Levels level, const std::string& message)
{
	if (!logger)
		return;

	logger->log(level, message + "\n");
}