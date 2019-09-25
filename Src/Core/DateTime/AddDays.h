#ifndef __ADD_DAYS_H
#define __ADD_DAYS_H

#include <date/date.h>

namespace Dt
{

date::year_month_day addDays(const date::year_month_day& date, int daysToAdd);

} // namespace Dt

#endif // __ADD_DAYS_H
