#include <gmock/gmock.h>
#include <codecvt>

namespace Tests
{

using namespace testing;

class StringTests : public testing::Test
{
public:
	StringTests(){};
};

TEST(StringTest, size_and_length_test)
{
	std::string foo = "aaabbbććć";

	EXPECT_EQ(foo.length(), 12);
	EXPECT_EQ(foo.size(), 12);

	std::wstring bar = L"aaabbbććć";

	EXPECT_EQ(bar.length(), 9);
	EXPECT_EQ(bar.size(), 9);	

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::wstring wide = converter.from_bytes(foo);

	EXPECT_EQ(wide.length(), 9);
	EXPECT_EQ(wide.size(), 9);	

	EXPECT_THAT(wide, Eq(bar));
}

} // namespace Tests
