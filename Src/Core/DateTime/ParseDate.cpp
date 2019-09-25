#include "Core/DateTime/ParseDate.h"

#include <Core/DateTime/DateFormat.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Dt
{
using namespace date;
using namespace std::string_literals;

Date parseDate(std::string_view dateString)
{
	auto days = sys_days();
	auto timezone = ""s;
	
	std::istringstream ss{dateString.data()};
	ss >> date::parse(conversionDateFormat, days, timezone);

	if (!bool(ss))
	{
		throw RuntimeError(
			"Cannot read "s + dateString.data() + " as date. "
			"Expected date format is " + printedDateFormat + ".");
	}

	return Date(days);
}

} // namespace Dt
