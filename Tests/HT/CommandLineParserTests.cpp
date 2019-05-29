#include <gmock/gmock.h>

#include <Core/Utils/Exceptions/RuntimeError.h>

#include "HT/Cli/CommandLineParser.h"
#include "HT/Cli/ParserResult.h"

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
	CommandLineParserTests(){}

	void checkResult(Cli::ParserResult actual, Cli::ParserResult expected)
	{
		EXPECT_THAT(actual.commandName, Eq(expected.commandName));
		EXPECT_THAT(actual.filter, Eq(expected.filter));
		EXPECT_THAT(actual.arguments, Eq(expected.arguments));
	}

	Cli::CommandLineParser parser;
};

TEST_F(CommandLineParserTests, returnsEmptyValuesWhenNoParameterIsPassed)
{
	int argc{1};
	char* argv[3] {"programName"_c};

	auto expected = Cli::ParserResult{"", "", Cli::Arguments{{"", ""}}};
	auto result = parser.parse(argc, argv);
	checkResult(result, expected);
}

TEST_F(CommandLineParserTests, parsesSimpleCommand)
{
	int argc{3};
	char* argv[3] {"programName"_c, "init"_c, "filePath"_c};

	auto result = parser.parse(argc, argv);
	auto expected = Cli::ParserResult{"init", "",
		Cli::Arguments{{"", "filePath"}}};

	checkResult(result, expected);
}

TEST_F(CommandLineParserTests, parsesCommandWithFilter)
{
	int argc{3};
	char* argv[3] {"ht"_c, "3"_c, "done"_c};

	auto expected = Cli::ParserResult{"done", "3", Cli::Arguments{{"", ""}}};
	auto result = parser.parse(argc, argv);
	checkResult(result, expected);
}

TEST_F(CommandLineParserTests, parsesCommandWithOptionalFlag)
{
	const int argc{3};
	char* argv[argc] = {"ht"_c, "command"_c, "-param"_c};

	auto expected = Cli::ParserResult("command", "",
		Cli::Arguments{{"", ""}, {"param", ""}});

	auto result = parser.parse(argc, argv);
	checkResult(result, expected);
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

TEST_F(CommandLineParserTests, throwsRuntimeErrorOnDuplicadedParameter)
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
		auto expected = "Redefinition of 'first' parameter";
		ASSERT_STREQ(err.what(), expected);
	}
}


} //namespace Tests
