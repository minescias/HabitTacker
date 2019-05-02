#include <gmock/gmock.h>

#include "HT/CommandLineParser.h"

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

	parser.parse(argc, argv);

	EXPECT_STREQ(parser.getCommandName().c_str(), "");
	EXPECT_STREQ(parser.getArguments().c_str(), "");
}

TEST_F(CommandLineParserTests, parsesSimpleCommand)
{
	int argc{3};
	char* argv[3] {"programName"_c, "init"_c, "filePath"_c};

	parser.parse(argc, argv);

	EXPECT_STREQ(parser.getCommandName().c_str(), "init");
	EXPECT_STREQ(parser.getArguments().c_str(), "filePath");
}

TEST_F(CommandLineParserTests, parsesCommandWithFilter)
{
	int argc{3};
	char* argv[3] {"ht"_c, "3"_c, "done"_c};

	parser.parse(argc, argv);
	EXPECT_STREQ(parser.getCommandName().c_str(), "done");
	EXPECT_STREQ(parser.getArguments().c_str(), "");
	EXPECT_STREQ(parser.getFilter().c_str(), "3");
}