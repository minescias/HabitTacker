#ifndef __LOGGER_H
#define __LOGGER_H

#include <string>

namespace Log
{

class Logger
{
public:
    Logger(bool enabled);

    void log(const std::string& message);

private:
    bool enabled;
};

} // namespace Log

#endif // __LOGGER_H
