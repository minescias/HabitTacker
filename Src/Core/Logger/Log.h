#ifndef __LOG_H
#define __LOG_H

#include <string>

#include <fmt/format.h>

#include "Core/Logger/Logger.h"

namespace Log
{
extern Log::Logger* logger;
void setLogger(Log::Logger* newLogger);

} // namespace Log

template<typename... TArgs>
void log(Log::Levels level, std::string_view message, TArgs... args)
{
	if (Log::logger && Log::logger->isLogEnabled(level))
		Log::logger->log(level, fmt::format(message, args...) + "\n");
}

template<typename... TArgs>
void log(std::string_view message, TArgs... args)
{
	log(Log::Levels::Common, message, args...);
}

#endif // __LOG_H
