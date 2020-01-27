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

TEST_F(TableTests, print_unicode_chaaracter_in_data)
{
	auto expected = R"(
One Two
--- ---
aą  ęe 
)";

	table.addColumn("One");
	table.addColumn("Two");

	table.addLine();
	table.setValue("One", "aą");
	table.setValue("Two", "ęe");

	checkPrintOutput(expected);
}

TEST_F(TableTests, get_column_width_from_longest_value)
{
	auto expected = R"(
One      Two         Three
-------- ----------- -----
raz      dwadzieścia trzy 
pierwszy drugi       :)   
)";

	table.addColumn("One");
	table.addColumn("Two");
	table.addColumn("Three");

	table.addLine();
	table.setValue("One", "raz");
	table.setValue("Two", "dwadzieścia");
	table.setValue("Three", "trzy");

	table.addLine();
	table.setValue("One", "pierwszy");
	table.setValue("Two", "drugi");
	table.setValue("Three", ":)");

	checkPrintOutput(expected);
}

TEST_F(TableTests, use_column_alias)
{
	auto expected = R"(
One Two Two       
--- --- ----------
raz dwa drugie dwa
)";

	table.addColumn("One");
	table.addColumn("Two_1", "Two");
	table.addColumn("Two_2", "Two");

	table.addLine();
	table.setValue("One", "raz");
	table.setValue("Two_1", "dwa");
	table.setValue("Two_2", "drugie dwa");

	checkPrintOutput(expected);
}

TEST_F(TableTests, use_index_when_setting_values)
{
	auto expected = R"(
One Two   Three
--- ----- -----
    aaaaa      
)";

	table.addColumn("One");
	table.addColumn("Two");
	table.addColumn("Three");

	table.addLine();
	auto columnIndex = table.getColumnIndex("Two");
	table.setValue(columnIndex, "aaaaa");
	
	checkPrintOutput(expected);
}

} // namespace Tests
