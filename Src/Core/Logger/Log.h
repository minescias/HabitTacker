#ifndef __LOG_H
#define __LOG_H

#include <string>

#include "Core/Logger/Logger.h"

namespace Log
{

void setLogger(Log::Logger* newLogger);

} // namespace Log

void log(const std::string& message, Log::Levels level = Log::Levels::Common);

#endif // __LOG_H
