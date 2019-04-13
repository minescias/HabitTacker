#ifndef __RUNTIME_ERROR_H
#define __RUNTIME_ERROR_H

#include <stdexcept>

class RuntimeError : public std::runtime_error
{
public:
    RuntimeError(const std::string& message);
};

#endif
