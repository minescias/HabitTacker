#ifndef __DATE_TIME_GETTER_H
#define __DATE_TIME_GETTER_H

#include "Core/DateTime/Timestamp.h"

namespace Dt
{

Timestamp getCurrentDate();

Timestamp getCurrentDateShiftByDays(int daysToAdd);

} // namespace Dt

#endif // __DATE_TIME_GETTER_H
