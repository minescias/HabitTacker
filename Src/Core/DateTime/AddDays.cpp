#include "Core/DateTime/AddDays.h"

namespace Dt
{
using namespace date;

year_month_day addDays(const year_month_day& date, int daysToAdd)
{
	return sys_days{date} + days{daysToAdd};
}

} // namespace Dt
