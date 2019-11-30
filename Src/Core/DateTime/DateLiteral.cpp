#include "Core/DateTime/DateLiteral.h"

#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/Operators.h>
#include <Core/DateTime/ParseDate.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Dt
{
Date DateLiteral::parse(const std::string& dateStr)
{
	if (dateStr == "today")
		return getCurrentDate();
	else if (dateStr == "yesterday")
		return getCurrentDate() - date::days{1};
	else if (dateStr == "tomorrow")
		return getCurrentDate() + date::days{1};

	return Dt::parseDate(dateStr);
}

} // namespace Dt
