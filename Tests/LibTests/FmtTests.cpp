#include <gmock/gmock.h>

#include <fmt/format.h>

namespace Tests
{
using namespace testing;

TEST(FmtTests, formatSimpleString)
{
	auto str = fmt::format("The answer is {}.", 42);
	auto expected = "The answer is 42.";

	ASSERT_THAT(str, Eq(expected));
}

} // namespace Tests
