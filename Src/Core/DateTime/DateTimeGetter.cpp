#include "Core/DateTime/DateTimeGetter.h"

#include "Core/DateTime/DateConsts.h"

namespace Dt
{

Timestamp getCurrentDate()
{
	auto today = std::time(nullptr);
	return today - (today % secondsInDay);
}

Timestamp getCurrentDateShiftByDays(int daysToAdd)
{
	auto today = std::time(nullptr);
	today = today - (today % secondsInDay);

	return getCurrentDate() + daysToAdd*secondsInDay;
}

} // namespace Dt
