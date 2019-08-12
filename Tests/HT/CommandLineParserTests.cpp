#include <gmock/gmock.h>

#include <vector>

#include "Core/Cli/CommandLineParser.h"
#include "Core/Cli/ParserResult.h"
#include "Core/Exceptions/RuntimeError.h"

namespace Tests
{

using namespace testing;

char* operator ""_c(const char* literal, size_t size)
{
	return const_cast<char*>(literal);
}

class CommandLineParserTests : public testing::Test
{
public:
    CommandLineParserTests() {}

    void checkResult(Cli::ParserResult actual, Cli::ParserResult expected,
        std::vector<std::string> flags, std::vector<std::string> parameters)
    {
        EXPECT_THAT(actual.getCommandName(), Eq(expected.getCommandName()));
        EXPECT_THAT(actual.getFilter(), Eq(expected.getFilter()));
        EXPECT_THAT(actual.getDefaultParameter(), Eq(expected.getDefaultParameter()));

        for (auto flag : flags)
            EXPECT_THAT(actual.getFlag(flag), Eq(expected.getFlag(flag)));

        for (auto param : parameters)
            EXPECT_THAT(actual.getParameter(param), Eq(expected.getParameter(param)));
    }

    Cli::CommandLineParser parser;
};

TEST_F(CommandLineParserTests, returnsEmptyValuesWhenNoParameterIsPassed)
{
	int argc{1};
	char* argv[3] {"programName"_c};

	auto expected = Cli::ParserResult();
	auto result = parser.parse(argc, argv);
	checkResult(result, expected, {}, {});
}

TEST_F(CommandLineParserTests, parsesSimpleCommand)
{
	int argc{3};
	char* argv[3] {"programName"_c, "init"_c, "filePath"_c};

	auto result = parser.parse(argc, argv);
	auto expected = Cli::ParserResult();
	expected.setCommandName("init");
	expected.setDefaultParameter("filePath");

	checkResult(result, expected, {}, {"filePath"});
}

TEST_F(CommandLineParserTests, parsesCommandWithFilter)
{
	int argc{3};
	char* argv[3] {"ht"_c, "3"_c, "done"_c};

	auto expected = Cli::ParserResult();
	expected.setCommandName("done");
	expected.setFilter("3");

	auto result = parser.parse(argc, argv);
	checkResult(result, expected, {}, {});
}

TEST_F(CommandLineParserTests, parsesCommandWithOptionalFlag)
{
	const int argc{3};
	char* argv[argc] = {"ht"_c, "command"_c, "-param"_c};

	auto expected = Cli::ParserResult();
	expected.setCommandName("command");
	expected.setFlag("param");

	auto result = parser.parse(argc, argv);
	checkResult(result, expected, {"param"}, {});
}

TEST_F(CommandLineParserTests, parsesCommandWithOptionalParameter)
{
	const int argc{3};
	char* argv[argc] = {"ht"_c, "command"_c, "-param=value"_c};

	auto expected = Cli::ParserResult();
	expected.setCommandName("command");
	expected.setParameter("param", "value");

	auto result = parser.parse(argc, argv);
	checkResult(result, expected, {}, {"param"});
}

TEST_F(CommandLineParserTests, throwsRuntimeErrorOnDuplicadedDefaultParameter)
{
	const int argc{4};
	char* argv[argc] = {"ht"_c, "command"_c, "first"_c, "second"_c};

	try
	{
		parser.parse(argc, argv);
		FAIL() << "RuntimeError expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Unknown command 'second'";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(CommandLineParserTests, throwsRuntimeErrorOnDuplicadedFlag)
{
	const int argc{4};
	char* argv[argc] = {"ht"_c, "command"_c, "-first"_c, "-first"_c};

	try
	{
		parser.parse(argc, argv);
		FAIL() << "RuntimeError expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Redefinition of flag 'first'";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(CommandLineParserTests, throwsRuntimeErrorOnDuplicadedParameter)
{
	const int argc{4};
	char* argv[argc] = {"ht"_c, "command"_c, "-first=1"_c, "-first=2"_c};

	try
	{
		parser.parse(argc, argv);
		FAIL() << "RuntimeError expected";
	}
	catch(RuntimeError& err)
	{
		auto expected = "Redefinition of parameter 'first'";
		ASSERT_STREQ(err.what(), expected);
	}
}


} //namespace Tests
