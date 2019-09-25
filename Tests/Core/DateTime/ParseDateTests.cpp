#include <gmock/gmock.h>

#include <date/date.h>

#include <Core/DateTime/ParseDate.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Tests
{
using namespace date;
using namespace testing;

TEST(ParseDateTests, parse_correct_date)
{
	auto dateString = "10.09.2019";

	auto expected = 2019_y / September / 10_d;
	auto date = Dt::parseDate(dateString);

	EXPECT_THAT(date, Eq(expected));
}

TEST(ParseDateTests, throws_error_when_parsing_date_with_incorrect_values)
{
	try
	{
		auto dateString = "99.99.2019";
		Dt::parseDate(dateString);
		FAIL() << "Expected runtime error";
	}
	catch (RuntimeError& err)
	{
		auto expected =
			"Cannot read 99.99.2019 as date. "
			"Expected date format is DD.MM.YYYY.";

		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ParseDateTests, throws_error_when_parsing_incorrect_date_string)
{
	try
	{
		auto dateString = "aaaaaaaaaaa";
		Dt::parseDate(dateString);
		FAIL() << "Expected runtime error";
	}
	catch (RuntimeError& err)
	{
		auto expected =
			"Cannot read aaaaaaaaaaa as date. "
			"Expected date format is DD.MM.YYYY.";

		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
