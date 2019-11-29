#include "Core/DateTime/Operators.h"

namespace date
{
year_month_day operator+(const year_month_day& date, const date::days& daysToAdd)
{
	return sys_days{date} + daysToAdd;
}

year_month_day operator-(const year_month_day& date, const date::days& daysToAdd)
{
	return sys_days{date} - daysToAdd;
}

year_month_day& operator+=(year_month_day& date, const days& daysToAdd)
{
	date = date + daysToAdd;
	return date;
}

year_month_day& operator-=(year_month_day& date, const days& daysToAdd)
{
	date = date - daysToAdd;
	return date;
}

year_month_day& operator++(year_month_day& date, int)
{
	date += days{1};
	return date;
}

year_month_day& operator--(year_month_day& date, int)
{
	date -= days{1};
	return date;
}

} // namespace date
