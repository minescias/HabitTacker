#include <gmock/gmock.h>

#include "HT/Cli/CommandLineParser.h"
#include "HT/Cli/ParserResult.h"

namespace Cli
{

bool operator==(const ParserResult &a, const ParserResult &b)
{
	return a.commandName == b.commandName
		&& a.filter == b.filter
		&& a.argument == b.argument;
}

} // namespace Cli

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

	Cli::CommandLineParser parser;
};

TEST_F(CommandLineParserTests, returnsEmptyValuesWhenNoParameterIsPassed)
{
	int argc{1};
	char* argv[3] {"programName"_c};

	auto expected = Cli::ParserResult{"", "", ""};
	auto result = parser.parse(argc, argv);
	ASSERT_THAT(result, Eq(expected));
}

TEST_F(CommandLineParserTests, parsesSimpleCommand)
{
	int argc{3};
	char* argv[3] {"programName"_c, "init"_c, "filePath"_c};

	auto expected = Cli::ParserResult{"init", "", "filePath"};
	auto result = parser.parse(argc, argv);
	ASSERT_THAT(result, Eq(expected));
}

TEST_F(CommandLineParserTests, parsesCommandWithFilter)
{
	int argc{3};
	char* argv[3] {"ht"_c, "3"_c, "done"_c};

	auto expected = Cli::ParserResult{"done", "3", ""};
	auto result = parser.parse(argc, argv);
	ASSERT_THAT(result, Eq(expected));
}

} //namespace Tests
