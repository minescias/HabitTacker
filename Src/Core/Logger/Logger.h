#ifndef __LOGGER_H
#define __LOGGER_H

#include <string>

namespace Log
{

class Logger
{
public:
    Logger();

    void log(const std::string& message);
};

} // namespace Log

#endif // __LOGGER_H
