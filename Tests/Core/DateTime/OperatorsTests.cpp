#include <gmock/gmock.h>

#include <Core/DateTime/Date.h>
#include <Core/DateTime/Operators.h>

namespace Tests
{
using namespace date;
using namespace testing;

TEST(DateOperatorsTests, add_days_test)
{
	auto date = 2019_y / September / 20_d;
	auto expected = 2019_y / September / 25_d;
	ASSERT_THAT(date + days(5), Eq(expected));
}

TEST(DateOperatorsTests, add_days_and_go_to_next_month_test)
{
	auto date = 2019_y / September / 28_d;
	auto expected = 2019_y / October / 3_d;
	ASSERT_THAT(date + days(5), Eq(expected));
}

TEST(DateOperatorsTests, subtract_days_test)
{
	auto date = 2019_y / September / 25_d;
	auto expected = 2019_y / September / 20_d;
	ASSERT_THAT(date - days(5), Eq(expected));
}

TEST(DateOperatorsTests, add_and_asign_days_test)
{
	auto date = 2019_y / September / 20_d;
	auto expected = 2019_y / September / 25_d;
	date += days(5);
	ASSERT_THAT(date, Eq(expected));
}

TEST(DateOperatorsTests, subtract_and_asign_days_test)
{
	auto date = 2019_y / September / 25_d;
	auto expected = 2019_y / September / 20_d;
	date -= days(5);
	ASSERT_THAT(date, Eq(expected));
}

TEST(DateOperatorsTests, increment_days_test)
{
	auto date = 2019_y / September / 20_d;
	auto expected = 2019_y / September / 21_d;
	ASSERT_THAT(date++, Eq(expected));
}

TEST(DateOperatorsTests, decrement_days_test)
{
	auto date = 2019_y / September / 21_d;
	auto expected = 2019_y / September / 20_d;
	ASSERT_THAT(date--, Eq(expected));
}

} // namespace Tests
