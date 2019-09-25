#ifndef __PARSE_DATE_H
#define __PARSE_DATE_H

#include <date/date.h>
#include <string_view>

namespace Dt
{

date::year_month_day parseDate(std::string_view dateString);

} // namespace Dt

#endif // __PARSE_DATE_H
