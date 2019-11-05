#include <gmock/gmock.h>

#include <date/date.h>
#include <fmt/format.h>

#include <Core/Format/DateFormatter.h>

namespace Tests
{

using namespace testing;
using namespace date;

TEST(DateFormatTests, first)
{
	auto date = 2019_y / September / 20;
	auto expected = "20.09.2019";
	auto actual = fmt::format("{}", date);

	ASSERT_THAT(actual, Eq(expected));
}

} // namespace Tests
