#include <gmock/gmock.h>

#include <Core/Cli/Table.h>

namespace Tests
{
using namespace testing;

class TableTests : public testing::Test
{
public:
	TableTests(){};

	void checkPrintOutput(const char* expected)
	{
		internal::CaptureStdout();
		table.print();
		auto result = testing::internal::GetCapturedStdout();
		ASSERT_STREQ(result.c_str(), expected);
	}

	Cli::Table table;
};

TEST_F(TableTests, print_header)
{
	auto expected = R"(
One Two Three
--- --- -----
)";

	table.addColumn("One");
	table.addColumn("Two");
	table.addColumn("Three");

	checkPrintOutput(expected);
}

TEST_F(TableTests, print_unicode_characters_in_header)
{
	auto expected = R"(
aaą eęe ćcccc
--- --- -----
)";

	table.addColumn("aaą");
	table.addColumn("eęe");
	table.addColumn("ćcccc");

	checkPrintOutput(expected);
}

TEST_F(TableTests, print_data)
{
	auto expected = R"(
One Two Three
--- --- -----
raz dwa trzy 
aa  bb  cc   
)";

	table.addColumn("One");
	table.addColumn("Two");
	table.addColumn("Three");

	table.addLine();
	table.setValue("One", "raz");
	table.setValue("Two", "dwa");
	table.setValue("Three", "trzy");

	table.addLine();
	table.setValue("One", "aa");
	table.setValue("Two", "bb");
	table.setValue("Three", "cc");

	checkPrintOutput(expected);
}

} // namespace Tests
