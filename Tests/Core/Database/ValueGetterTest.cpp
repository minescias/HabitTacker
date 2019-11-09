#include <gmock/gmock.h>

#include <Core/Database/ValueGetter.h>
#include <Core/DateTime/Date.h>
#include <Core/Exceptions/LogicError.h>

namespace Tests
{
using namespace testing;

// getting values
TEST(ValueGetterTest, gets_value_as_string)
{
	EXPECT_THAT(Db::getVal<std::string>("", "abc"), Eq("abc"));
}

TEST(ValueGetterTest, gets_value_as_int)
{
	EXPECT_THAT(Db::getVal<int>("", "123"), Eq(123));
}

TEST(ValueGetterTest, gets_value_as_double)
{
	EXPECT_THAT(Db::getVal<double>("", "1.23"), Eq(1.23));
}

TEST(ValueGetterTest, gets_value_as_date)
{
	using namespace date;
	EXPECT_THAT(Db::getVal<Dt::Date>("", "18160"), Eq(2019_y / September / 21_d));
}

TEST(ValueGetterTest, gets_null_value_as_nullopt)
{
	EXPECT_THAT(Db::getVal<std::optional<int>>("", ""), Eq(std::nullopt));
}

TEST(ValueGetterTest, gets_null_value_as_optional)
{
	using std::optional;
	EXPECT_THAT(Db::getVal<optional<int>>("", "23"), Eq(optional<int>(23)));
}

// null value error handling
TEST(ValueGetterTest, throws_logic_error_when_casting_null_to_int)
{
	try
	{
		Db::getVal<int>("foo", "");
		FAIL() << "Expected logic error";
	}
	catch (LogicError& err)
	{
		auto expected = "Db: Cannot cast null value of column 'foo' to type int";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ValueGetterTest, throws_logic_error_when_casting_null_to_double)
{
	try
	{
		Db::getVal<double>("foo", "");
		FAIL() << "Expected logic error";
	}
	catch (LogicError& err)
	{
		auto expected =
			"Db: Cannot cast null value of column 'foo' to type double";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ValueGetterTest, throws_logic_error_when_casting_null_to_date)
{
	try
	{
		Db::getVal<Dt::Date>("foo", "");
		FAIL() << "Expected logic error";
	}
	catch (LogicError& err)
	{
		auto expected =
			"Db: Cannot cast null value of column 'foo' to type date::year_month_day";
		ASSERT_STREQ(err.what(), expected);
	}
}

// casting errors
TEST(ValueGetterTest, throws_logic_error_when_cannot_cast_to_int)
{
	try
	{
		Db::getVal<int>("foo", "bar");
		FAIL() << "Expected logic error";
	}
	catch (LogicError& err)
	{
		auto expected =
			"Db: Cannot cast value 'bar' of column 'foo' to type int";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ValueGetterTest, throws_logic_error_when_cannot_cast_to_double)
{
	try
	{
		Db::getVal<double>("foo", "bar");
		FAIL() << "Expected logic error";
	}
	catch (LogicError& err)
	{
		auto expected =
			"Db: Cannot cast value 'bar' of column 'foo' to type double";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ValueGetterTest, throws_logic_error_when_cannot_cast_to_date)
{
	try
	{
		Db::getVal<Dt::Date>("foo", "bar");
		FAIL() << "Expected logic error";
	}
	catch (LogicError& err)
	{
		auto expected =
			"Db: Cannot cast value 'bar' of column 'foo' to type date::year_month_day";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
