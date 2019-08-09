#include <gmock/gmock.h>

#include "Core/DateTime/DateTime.h"
#include "Core/Exceptions/RuntimeError.h"

namespace Tests
{

using namespace testing;

TEST(DateTimeTest, createsDateTimeFromString)
{
	auto date = Dt::DateTime{"10-05-2019"};
	auto unixTime = Dt::Timestamp{1557446400};

	ASSERT_THAT(date.unixTime(), Eq(unixTime));
}

TEST(DateTimeTests, printsDate)
{
	auto date = Dt::DateTime{1557446400};
	ASSERT_STREQ(date.dateString().c_str(), "10-05-2019");
}

TEST(DateTimeTests, addDayToDateTime)
{
	auto date = Dt::DateTime("10-05-2019").addDays(1);
	auto date2 = Dt::DateTime("10-05-2019").addDays(5);

	ASSERT_THAT(date.unixTime(), Dt::DateTime("11-05-2019").unixTime());
	ASSERT_THAT(date2.unixTime(), Dt::DateTime("15-05-2019").unixTime());
}

TEST(DateTimeTests, getDayOfWeek)
{
	ASSERT_THAT(Dt::DateTime("14-05-2019").weekDay(), Eq(2));
	ASSERT_THAT(Dt::DateTime("15-05-2019").weekDay(), Eq(3));
}

TEST(DateTimeTests, subtractionOfTwoDatesRerurnsDuration)
{
	auto duration = Dt::DateTime{"20-05-2019"} - Dt::DateTime{"10-05-2019"};
	ASSERT_THAT(duration.getDays(), Eq(10));
}

TEST(DateTimeTests, throwRuntimeErrorOnBadDateFormat)
{
	try
	{
		Dt::DateTime("123-324-43652");
		FAIL() << "RuntimeError expected";
	}
	catch (RuntimeError& err)
	{
		auto expected = "Cannot convert '123-324-43652' to date. "
			"Expected date format is DD-MM-YYYY";

		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(DateTimeTests, throwRuntimeErrorOnBadDateValue)
{
	try
	{
		Dt::DateTime("99-01-2000");
		FAIL() << "RuntimeError expected";
	}
	catch (RuntimeError& err)
	{
		auto expected = "Cannot convert '99-01-2000' to date. "
			"Expected date format is DD-MM-YYYY";

		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
