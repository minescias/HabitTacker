// \d{2}-\d{2}-\d{4}

#include <gmock/gmock.h>

#include <regex>

namespace Tests
{

TEST(RegexTest, matchEntireStringTests)
{
	auto regex = std::regex(R"r(\d{2}-\d{2}-\d{4})r");
	auto match = std::cmatch();

	EXPECT_TRUE(std::regex_match("11-11-1111", match, regex));
	EXPECT_FALSE(std::regex_match("11-11-1111xx", match, regex));
	EXPECT_FALSE(std::regex_match("xx11-11-1111", match, regex));
	EXPECT_FALSE(std::regex_match("xx11-11-1111xx", match, regex));
}

} // namespace Tests
