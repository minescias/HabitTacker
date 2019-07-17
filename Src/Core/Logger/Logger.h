#ifndef __LOGGER_H
#define __LOGGER_H

#include <memory>
#include <string>

#include <Core/Logger/LogConfig.h>

namespace Log
{

class Logger
{
public:
    Logger(std::unique_ptr<Config> config);

    void log(const std::string& message, Levels level);

private:
    bool isLogEnabled(Levels level);

private:
    std::unique_ptr<Config> config;
};

} // namespace Log

#endif // __LOGGER_H
