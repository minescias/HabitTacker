#include <gmock/gmock.h>

#include "Core/Utils/Exceptions/LogicError.h"
#include "Src/Core/Database/ValueGetter.h"

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

TEST(ValueGetterTest, gets_value_as_time_t)
{
	EXPECT_THAT(Db::getVal<time_t>("", "123456789"), Eq(123456789));
}

// null value error handling
TEST(ValueGetterTest, throws_logic_error_when_casting_null_to_int)
{
	try
	{
		Db::getVal<int>("foo", "");
		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
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
	catch(LogicError& err)
	{
		auto expected = "Db: Cannot cast null value of column 'foo' to type double";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ValueGetterTest, throws_logic_error_when_casting_null_to_time_t)
{
	try
	{
		Db::getVal<time_t>("foo", "");
		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "Db: Cannot cast null value of column 'foo' to type time_t";
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
	catch(LogicError& err)
	{
		auto expected = "Db: Cannot cast value 'bar' of column 'foo' to type int";
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
	catch(LogicError& err)
	{
		auto expected = "Db: Cannot cast value 'bar' of column 'foo' to type double";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST(ValueGetterTest, throws_logic_error_when_cannot_cast_to_time_t)
{
	try
	{
		Db::getVal<time_t>("foo", "bar");
		FAIL() << "Expected logic error";
	}
	catch(LogicError& err)
	{
		auto expected = "Db: Cannot cast value 'bar' of column 'foo' to type time_t";
		ASSERT_STREQ(err.what(), expected);
	}
}

} // namespace Tests
