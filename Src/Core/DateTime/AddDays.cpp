#include "Core/DateTime/AddDays.h"

namespace Dt
{
using namespace date;

Date addDays(const Date& date, int daysToAdd)
{
	return sys_days{date} + days{daysToAdd};
}

} // namespace Dt
