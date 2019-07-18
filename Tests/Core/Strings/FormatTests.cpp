#include <gmock/gmock.h>

#include <Core/Strings/Format.h>
namespace Tests
{

using namespace testing;

class FormatTests : public testing::Test
{
public:
	FormatTests(){};
};

TEST(FormatTest, format_text_without_parameters)
{
	auto expected = "onetwothree";
	auto actual = format("onetwothree");

	ASSERT_THAT(actual, Eq(expected));
}

TEST(FormatTest, format_text_with_one_parameter_of_string_type)
{
	auto expected = "firts parameter is: foo";
	auto actual = format("firts parameter is: %1%", "foo");

	ASSERT_THAT(actual, Eq(expected));
}

} // namespace Tests
