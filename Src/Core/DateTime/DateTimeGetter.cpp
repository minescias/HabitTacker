#include "Core/DateTime/DateTimeGetter.h"

#include <ctime>

namespace Dt
{

const auto secondsInDay{86400}; //24 * 60 * 60

Timestamp getCurrentDate()
{
	auto today = std::time(nullptr);
	return today - (today % secondsInDay);
}

} // namespace Dt
