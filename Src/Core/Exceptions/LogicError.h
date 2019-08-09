#ifndef __LOGIC_ERROR_H
#define __LOGIC_ERROR_H

#include <stdexcept>

class LogicError : public std::logic_error
{
public:
    LogicError(const std::string& message);
};

#endif
