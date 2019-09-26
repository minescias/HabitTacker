#include <gmock/gmock.h>

#include <Core/DateTime/FormatDate.h>

namespace Tests
{

using namespace date;
using namespace testing;

class FormatDate : public testing::Test
{
public:
	FormatDate(){};
};

TEST(FormatDateTests, format)
{
	auto date = 2019_y/September/10_d;

	auto dateString = Dt::formatDate(date);
	auto expected = "10.09.2019";

	EXPECT_THAT(dateString, Eq(expected));
}

} // namespace Tests
