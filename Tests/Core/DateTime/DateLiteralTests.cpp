#include <gmock/gmock.h>

#include "Core/DateTime/DateLiteral.h"
#include "Core/DateTime/DateTime.h"
#include "Core/DateTime/DateTimeGetter.h"
#include "Core/Utils/Exceptions/RuntimeError.h"

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

TEST_F(DateLiteralTests, acceptsToday)
{
	checkSimpleLiteral("today", 0);
	checkSimpleLiteral("yesterday", -1);
	checkSimpleLiteral("tomorrow", 1);
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
		auto expected = "Cannot read 'ssssssssssss' as date";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
