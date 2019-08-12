#include <gmock/gmock.h>

#include "Core/Cli/ParserResult.h"

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

TEST(ParserResultTests, set_and_get_default_parameter)
{
	Cli::ParserResult pr;

	EXPECT_THAT(pr.getDefaultParameter(), Eq(""));
	pr.setDefaultParameter("defaultParameter");
	EXPECT_THAT(pr.getDefaultParameter(), Eq("defaultParameter"));
}

TEST(ParserResultTests, set_and_get_parameter)
{
	Cli::ParserResult pr;
	pr.setParameter("param_name", "param value");

	EXPECT_THAT(pr.getParameter("param_that_is_not_set"), Eq(""));
	EXPECT_THAT(pr.getParameter("param_name"), Eq("param value"));
}

TEST(ParserResultTests, sets_and_gets_command_name)
{
	Cli::ParserResult pr;

	EXPECT_THAT(pr.getCommandName(), Eq(""));
	pr.setCommandName("defaultParameter");
	EXPECT_THAT(pr.getCommandName(), Eq("defaultParameter"));
}

} // namespace Tests
