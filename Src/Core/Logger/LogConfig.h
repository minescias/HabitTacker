#ifndef __LOG_CONFIG_H
#define __LOG_CONFIG_H

#include <set>

namespace Log
{

enum class Levels {
    Common,
    Error,
    Sql
};

struct Config
{
	std::set<Levels> levels;
	bool enabled = false;
};

} // namespace Log

#endif // __LOG_CONFIG_H
