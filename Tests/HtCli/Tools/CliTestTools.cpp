#include "Tests/HtCli/Tools/CliTestTools.h"

#include <algorithm>

#include "CLI/App.hpp"
#include "gtest/gtest.h"

namespace Tests
{
void parseArguments(CLI::App* app, std::vector<std::string> arguments)
{
	std::reverse(arguments.begin(), arguments.end());
	app->parse(arguments);
}

void parseAndThrowError(
	CLI::App* app, std::vector<std::string> arguments, const std::string& errorMsg)
{
	try
	{
		parseArguments(app, arguments);
		FAIL() << "ParseError expected";
	}
	catch (const CLI::ParseError& err)
	{
		ASSERT_STREQ(errorMsg.c_str(), err.what());
	}
}

} // namespace Tests
