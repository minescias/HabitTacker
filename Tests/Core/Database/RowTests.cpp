#include <gmock/gmock.h>

#include <Core/Database/Row.h>
#include <Core/Exceptions/LogicError.h>

namespace Tests
{

using namespace testing;

class RowTests : public testing::Test
{
public:
	RowTests(){};
};

TEST(RowTests, allows_to_set_and_get_value_as_string)
{
	Db::DatasetHeader header = {{"aaa", 0}, {"bbb", 1}};

	auto row = Db::Row(&header);
	row.set("aaa", "111");
	row.set("bbb", "222");

	EXPECT_THAT(row.get<std::string>("aaa"), Eq("111"));
	EXPECT_THAT(row.get<std::string>("bbb"), Eq("222"));
}

TEST(RowTests, gets_and_casts_value_to_desired_type)
{
	Db::DatasetHeader header = {{"aaa", 0}, {"bbb", 1}};

	auto row = Db::Row(&header);
	row.set("aaa", "111");
	row.set("bbb", "2.22");

	EXPECT_THAT(row.get<int>("aaa"), Eq(111));
	EXPECT_THAT(row.get<double>("bbb"), Eq(2.22));
}

TEST(RowTests, throws_logic_error_when_getting_from_column_that_does_not_exist)
{
	Db::DatasetHeader header = {{"foo", 0}};
	auto row = Db::Row(&header);
	row.set("foo", "111");

	try
	{
		row.get<int>("bar");
		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "Db: Column 'bar' does not exist";
		ASSERT_STREQ(err.what(), expected);
	}
}



} // namespace Tests
