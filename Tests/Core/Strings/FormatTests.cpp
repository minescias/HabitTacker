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

TEST(FormatTest, formats_text_without_parameters)
{
	auto expected = "onetwothree";
	auto actual = format("onetwothree");

	ASSERT_THAT(actual, Eq(expected));
}

TEST(FormatTest, formats_text_with_one_parameter_of_string_type)
{
	auto expected = "firts parameter is: foo";
	auto actual = format("firts parameter is: %1%", "foo");

	ASSERT_THAT(actual, Eq(expected));
}

TEST(FormatTest, formats_text_with_one_parameter_of_any_type)
{
	auto expected = "firts parameter is: foo";
	auto actual = format("firts parameter is: %1%", "foo");

	ASSERT_THAT(format("int: %1% OK", 10), Eq("int: 10 OK"));
	ASSERT_THAT(format("double: %1% OK", 10.0), Eq("double: 10 OK"));
	ASSERT_THAT(format("double: %1% OK", 10.3), Eq("double: 10.3 OK"));
	ASSERT_THAT(format("double: %1% OK", 10.3534), Eq("double: 10.3534 OK"));
}

TEST(FormatTests, formats_text_with_more_than_one_parameter)
{
	auto expected = "abc; 123, def 4.56 ghi";
	auto actual = format("abc; %1%, def %2% ghi", 123, 4.56);

	ASSERT_THAT(actual, Eq(expected));
	
}

} // namespace Tests
