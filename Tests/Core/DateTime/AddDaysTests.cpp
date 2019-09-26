#include <gmock/gmock.h>

#include <date/date.h>

#include <Core/DateTime/AddDays.h>

namespace Tests
{

using namespace date;
using namespace testing;

TEST(AddDaysTests, adds_days_to_date)
{
	auto date = 2019_y/September/20_d;
	auto newDate = Dt::addDays(date, 5);

	auto expected = 2019_y/September/25_d;

	ASSERT_EQ(newDate, expected);
}

TEST(AddDaysTests, subtract_days_from_date)
{
	auto date = 2019_y/September/25_d;
	auto newDate = Dt::addDays(date, -5);

	auto expected = 2019_y/September/20_d;

	ASSERT_EQ(newDate, expected);
}

} // namespace Tests
