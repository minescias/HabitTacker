#include "Core/DateTime/DateTimeGetter.h"

#include "Core/DateTime/DateConsts.h"

namespace Dt
{

using namespace date;

Date getCurrentDate2()
{
	auto timepoint = std::chrono::system_clock::now();
	// auto d = date::floor<date::days>(tp);
	auto date = date::floor<date::days>(timepoint);// 	auto days = sys_days{currentDate};
	return date; //2019_y/September/12_d;
}

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
