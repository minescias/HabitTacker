#include <gmock/gmock.h>

#include <type_traits>

#include <date/date.h>

namespace Tests
{

using namespace testing;

TEST(TypeTraitsTests, is_integral)
{
	EXPECT_TRUE(std::is_integral_v<int>);
	
	EXPECT_FALSE(std::is_integral_v<date::year_month_day>);
}

} // namespace Tests
