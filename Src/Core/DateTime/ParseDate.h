#ifndef __PARSE_DATE_H
#define __PARSE_DATE_H

#include <string_view>

#include <Core/DateTime/Date.h>

namespace Dt
{

Date parseDate(std::string_view dateString);

} // namespace Dt

#endif // __PARSE_DATE_H
