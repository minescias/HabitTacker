#include "Core/DateTime/ParseDate.h"

#include <Core/Exceptions/RuntimeError.h>

namespace Dt
{
using namespace date;
using namespace std::string_literals;

date::year_month_day parseDate(std::string_view dateString)
{
	auto days = sys_days();
	auto timezone = ""s;
	
	std::istringstream ss{dateString.data()};
	ss >> date::parse("%d.%m.%Y", days, timezone);

	if (!bool(ss))
	{
		throw RuntimeError(
			"Cannot read "s + dateString.data() + " as date. "
			"Expected date format is DD.MM.YYYY.");
	}

	return year_month_day(days);
}

} // namespace Dt
