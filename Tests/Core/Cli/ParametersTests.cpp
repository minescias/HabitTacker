#include <gmock/gmock.h>

#include "Core/Cli/Parameters.h"

namespace Tests
{

using namespace testing;

TEST(ParametersTests, sets_and_gets_filter)
{
	Cli::Parameters pr;
	pr.setFilter("2");

	ASSERT_THAT(pr.getFilter(), Eq("2"));
}

TEST(ParametersTests, sets_and_gets_flags)
{
	Cli::Parameters pr;
	pr.setFlag("reset");

	EXPECT_TRUE(pr.getFlag("reset"));
	EXPECT_FALSE(pr.getFlag("init"));
}

TEST(ParametersTests, set_and_get_default_parameter)
{
	Cli::Parameters pr;

	EXPECT_THAT(pr.getDefaultParameter(), Eq(""));
	pr.setDefaultParameter("defaultParameter");
	EXPECT_THAT(pr.getDefaultParameter(), Eq("defaultParameter"));
}

TEST(ParametersTests, set_and_get_parameter)
{
	Cli::Parameters pr;
	pr.setParameter("param_name", "param value");

	EXPECT_THAT(pr.getParameter("param_that_is_not_set"), Eq(""));
	EXPECT_THAT(pr.getParameter("param_name"), Eq("param value"));
}

TEST(ParametersTests, sets_and_gets_command_name)
{
	Cli::Parameters pr;

	EXPECT_THAT(pr.getCommandName(), Eq(""));
	pr.setCommandName("defaultParameter");
	EXPECT_THAT(pr.getCommandName(), Eq("defaultParameter"));
}

} // namespace Tests
