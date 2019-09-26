#include "Core/DateTime/DateTimeGetter.h"

namespace Dt
{

Date getCurrentDate()
{
	auto timepoint = std::chrono::system_clock::now();
	return date::floor<date::days>(timepoint);
}

} // namespace Dt
