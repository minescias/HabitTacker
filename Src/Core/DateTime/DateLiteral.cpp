#include "Core/DateTime/DateLiteral.h"

#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/DateTime.h>
#include <Core/Utils/Exceptions/RuntimeError.h>

namespace Dt
{

DateLiteral::DateLiteral()
{
}

Timestamp DateLiteral::parse(const std::string& date)
{
	if (date == "today")
		return getCurrentDate();
	else if (date == "yesterday")
		return getCurrentDateShiftByDays(-1);
	else if (date == "tomorrow")
		return getCurrentDateShiftByDays(1);

	throw RuntimeError("Cannot read '" + date +"' as date");
}

} // namespace Dt
