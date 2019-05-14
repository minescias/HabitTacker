#include "Core/DateTime/Duration.h"

#include "Core/DateTime/DateConsts.h"

namespace Dt
{

Duration::Duration(Dt::Timestamp timestamp)
	:timestamp(timestamp)
{
}

int Duration::getDays() const
{
	return timestamp/secondsInDay;
}

} // namespace Dt
