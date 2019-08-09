#include <gmock/gmock.h>

#include "Core/DateTime/DateLiteral.h"
#include "Core/DateTime/DateTime.h"
#include "Core/DateTime/DateTimeGetter.h"
#include "Core/Exceptions/RuntimeError.h"

namespace Tests
{

using namespace Dt;
using namespace testing;

class DateLiteralTests : public testing::Test
{
public:
	DateLiteralTests(){};

	void checkSimpleLiteral(const std::string& literal, int daysFromToday)
	{
		auto expected = getCurrentDateShiftByDays(daysFromToday);
		auto actual = DateLiteral().parse(literal);

		EXPECT_THAT(actual, Eq(expected)) << "Literal:" << literal;
	}
};

TEST_F(DateLiteralTests, acceptsDateName)
{
	checkSimpleLiteral("today", 0);
	checkSimpleLiteral("yesterday", -1);
	checkSimpleLiteral("tomorrow", 1);
}

TEST_F(DateLiteralTests, acceptsDateString)
{
	auto expected = Dt::DateTime("10-01-2015").unixTime();
	auto actual = DateLiteral().parse("10-01-2015");

	EXPECT_THAT(actual, Eq(expected)) << "Literal:" << "10-01-2015";
}

TEST_F(DateLiteralTests, throwsRuntimeErrorOnUnknownLiteral)
{
	try
	{
		DateLiteral().parse("ssssssssssss");
		FAIL() << "Runtime error expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Cannot convert 'ssssssssssss' to date. "
			"Expected date format is DD-MM-YYYY";

		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
