#include <gmock/gmock.h>

#include <iostream>

#include <date/date.h>

namespace Tests
{
using namespace std::string_literals;
using namespace date;
using namespace testing;

TEST(DateTests, convert_cpp_date_to_sql_format)
{
	constexpr auto date = 05_d / September / 2019_y;
	constexpr auto daysSinceEpoch = sys_days(date);

	ASSERT_EQ(daysSinceEpoch.time_since_epoch().count(), 18144);
}

TEST(DateTests, convert_sql_date_to_cpp_format)
{
	constexpr auto daysSinceEpoch = date::days(18144);
	constexpr auto sysDate = sys_days(daysSinceEpoch);
	constexpr auto cppDate = year_month_day(sysDate);
	constexpr auto expectedDate = 05_d / September / 2019_y;

	ASSERT_THAT(cppDate, Eq(expectedDate));
}

TEST(DateTests, format_date)
{
	constexpr auto date = 05_d / September / 2019_y;
	auto formattedDate = format("%d.%m.%Y", date);

	auto expected = "05.09.2019";

	ASSERT_EQ(formattedDate, expected);
}

TEST(DateTests, parse_date)
{
	std::stringstream ss;
	ss << "05.09.2019";

	auto days = sys_days();
	auto timezone = ""s;
	ss >> date::parse("%d.%m.%Y", days, timezone);
	// auto parsedDate = date::parse("%d.%m.%Y", days);

	constexpr auto expectedDate = 05_d / September / 2019_y;
	auto parsedDate = year_month_day(days);

	// ASSERT_THAT(parsedDate, Eq(expectedDate));
	EXPECT_THAT(parsedDate.day(), Eq(expectedDate.day()));
	EXPECT_THAT(parsedDate.month(), Eq(expectedDate.month()));
	EXPECT_THAT(parsedDate.year(), Eq(expectedDate.year()));
}

TEST(DateTests, parse_error_handling)
{
	auto days = sys_days();
	auto timezone = ""s;

	std::stringstream incorrectValues;
	incorrectValues << "05.30.2019";

	incorrectValues >> date::parse("%d.%m.%Y", days, timezone);
	EXPECT_THAT(days, Eq(sys_days()));

	std::stringstream incorrectDateFormat;
	incorrectDateFormat << "2019.31.12";

	incorrectDateFormat >> date::parse("%d.%m.%Y", days, timezone);
	EXPECT_THAT(days, Eq(sys_days()));
}

TEST(DateTests, add_days)
{
	constexpr auto expectedDate = 15_d / September / 2019_y;

	auto date = 05_d / September / 2019_y;
	date = sys_days{date} + days{10};

	EXPECT_THAT(date.day(), Eq(expectedDate.day()));
	EXPECT_THAT(date.month(), Eq(expectedDate.month()));
	EXPECT_THAT(date.year(), Eq(expectedDate.year()));
}

} // namespace Tests
