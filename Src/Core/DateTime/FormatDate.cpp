#include "Core/DateTime/FormatDate.h"

namespace Dt
{

std::string formatDate(date::year_month_day date)
{
	return date::format("%d.%m.%Y", date);
}

} // namespace Dt
