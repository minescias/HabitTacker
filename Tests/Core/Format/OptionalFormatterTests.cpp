#include <gmock/gmock.h>

#include <optional>

#include <fmt/format.h>

#include <Core/Format/OptionalFormatter.h>

namespace Tests
{
using namespace testing;

TEST(OptionalFormatterTetsts, format_nullopt_as_null)
{
	auto actual = fmt::format("format nullopt: {}", std::nullopt);
	auto expected = "format nullopt: 'null'";

	EXPECT_THAT(actual, Eq(expected));
}

TEST(OptionalFormatterTetsts, format_unitialized_optional_as_null)
{
	auto actual = fmt::format("format nullopt: {}", std::optional<int>());
	auto expected = "format nullopt: 'null'";

	EXPECT_THAT(actual, Eq(expected));
}

TEST(OptionalFormatterTetsts, format_initialized_optional_as_its_type)
{
	auto actual = fmt::format("format optional int: {}", std::optional<int>(42));
	auto expected = "format optional int: 42";

	EXPECT_THAT(actual, Eq(expected));
}

} // namespace Tests
