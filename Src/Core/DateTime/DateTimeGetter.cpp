#include "Core/DateTime/DateTimeGetter.h"

#include "Core/DateTime/DateConsts.h"

namespace Dt
{

Timestamp getCurrentDate()
{
	auto today = std::time(nullptr);
	return today - (today % secondsInDay);
}

} // namespace Dt
