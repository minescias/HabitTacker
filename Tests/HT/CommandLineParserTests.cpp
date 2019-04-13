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

	CommandLineParser parser;
};

TEST_F(CommandLineParserTests, returnsEmptyValuesWhenNoParameterIsPassed)
{
	int argc{1};
	char* argv[3] {"programName"_c};

	parser.parse(argc, argv);

	EXPECT_STREQ(parser.getCommandName().c_str(), "");
	EXPECT_TRUE(parser.getArguments().empty());
}

TEST_F(CommandLineParserTests, parsesSimpleCommand)
{
	int argc{3};
	char* argv[3] {"programName"_c, "init"_c, "filePath"_c};

	parser.parse(argc, argv);

	EXPECT_STREQ(parser.getCommandName().c_str(), "init");
	EXPECT_THAT(parser.getArguments(), ElementsAre("filePath"));
}
