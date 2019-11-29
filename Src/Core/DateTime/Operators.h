#ifndef __OPERATORS_H
#define __OPERATORS_H

#include <date/date.h>

namespace date
{
year_month_day operator+(const year_month_day& date, const days& daysToAdd);
year_month_day operator-(const year_month_day& date, const days& daysToAdd);

year_month_day& operator+=(year_month_day& date, const days& daysToAdd);
year_month_day& operator-=(year_month_day& date, const days& daysToAdd);

year_month_day& operator++(year_month_day& date, int);
year_month_day& operator--(year_month_day& date, int);

} // namespace date

#endif // __OPERATORS_H
