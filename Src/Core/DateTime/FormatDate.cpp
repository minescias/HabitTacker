#include "Core/DateTime/FormatDate.h"

#include <Core/DateTime/DateFormat.h>

namespace Dt
{

std::string formatDate(Date date)
{
	return date::format(conversionDateFormat, date);
}

} // namespace Dt
