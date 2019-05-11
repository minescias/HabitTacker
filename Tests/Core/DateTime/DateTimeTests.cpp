#include <gmock/gmock.h>

#include "Core/DateTime/DateTime.h"
#include "Core/Utils/Exceptions/RuntimeError.h"

/*
	typedef daty
	const formatu daty

	lista funkcjonalności:
	* OK pobieranie daty z time_t
	* OK pobieranie daty z stringa
	* walidacja poprawności formatu daty i wartości liczb
*/

namespace Tests
{

using namespace testing;

TEST(DateTimeTest, createsDateTimeFromString)
{
	auto date = Dt::DateTime{"10-05-2019"};
	auto unixTime = Dt::Timestamp{1557446400}; // 1557446400

	ASSERT_THAT(date.unixTime(), Eq(unixTime));
}

TEST(DateTimeTests, printsDate)
{
	auto date = Dt::DateTime{1557446400}; // 1557446400
	ASSERT_STREQ(date.dateString().c_str(), "10-05-2019");
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
