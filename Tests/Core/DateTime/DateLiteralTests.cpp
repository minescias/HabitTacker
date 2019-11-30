#include <gmock/gmock.h>

#include <Core/DateTime/DateLiteral.h>
#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/Operators.h>
#include <Core/Exceptions/RuntimeError.h>

namespace Tests
{
using namespace date;
using namespace testing;

class DateLiteralTests : public testing::Test
{
public:
	DateLiteralTests(){};

	void checkSimpleLiteral(const std::string& literal, int daysFromToday)
	{
		auto expected = Dt::getCurrentDate() + days(daysFromToday);
		auto actual = Dt::DateLiteral().parse(literal);

		EXPECT_THAT(actual, Eq(expected));
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
	auto expected = 2015_y / January / 10_d;
	auto actual = Dt::DateLiteral().parse("10.01.2015");

	EXPECT_THAT(actual, Eq(expected));
}

TEST_F(DateLiteralTests, throwsRuntimeErrorOnUnknownLiteral)
{
	try
	{
		Dt::DateLiteral().parse("ssssssssssss");
		FAIL() << "Runtime error expected";
	}
	catch (RuntimeError& err)
	{
		auto expected =
			"Cannot read ssssssssssss as date. "
			"Expected date format is DD.MM.YYYY.";

		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
