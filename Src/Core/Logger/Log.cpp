#include "Core/Logger/Log.h"

namespace Log
{
Log::Logger* logger;

void setLogger(Log::Logger* newLogger)
{
	logger = newLogger;
}

} // namespace Log
