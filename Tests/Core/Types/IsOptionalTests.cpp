#include <gmock/gmock.h>

#include <Core/Types/IsOptional.h>

namespace Tests
{
using namespace testing;

TEST(IsOptionalTests, returns_false_when_variable_is_not_optional)
{
	auto opt = std::make_optional<double>(22.12);

	EXPECT_FALSE(::Types::isOptional_v<int>);
	EXPECT_TRUE(::Types::isOptional_v<decltype(opt)>);
}

} // namespace Tests
