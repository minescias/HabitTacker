#include <gmock/gmock.h>

#include "HT/Cli/ParserResult.h"

namespace Tests
{

using namespace testing;

TEST(ParserResultTests, sets_and_gets_filter)
{
	Cli::ParserResult pr;
	pr.setFilter("2");

	ASSERT_THAT(pr.getFilter(), Eq("2"));
}

TEST(ParserResultTests, sets_and_gets_flags)
{
	Cli::ParserResult pr;
	pr.setFlag("reset");

	EXPECT_TRUE(pr.getFlag("reset"));
	EXPECT_FALSE(pr.getFlag("init"));
}


} // namespace Tests
