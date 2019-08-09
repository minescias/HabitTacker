#include "Core/DateTime/DateLiteral.h"

#include <Core/DateTime/DateTime.h>
#include <Core/DateTime/DateTimeGetter.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Dt
{

DateLiteral::DateLiteral()
{
}

Timestamp DateLiteral::parse(const std::string& dateStr)
{
	if (dateStr == "today")
		return getCurrentDate();
	else if (dateStr == "yesterday")
		return getCurrentDateShiftByDays(-1);
	else if (dateStr == "tomorrow")
		return getCurrentDateShiftByDays(1);

	return Dt::DateTime(dateStr).unixTime();
}

} // namespace Dt
