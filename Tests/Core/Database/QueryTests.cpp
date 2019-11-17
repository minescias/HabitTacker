#include <gmock/gmock.h>

#include <memory>
#include <optional>

#include "Core/Database/Database.h"
#include "Core/Database/Dataset.h"
#include "Core/Database/Query.h"
#include "Core/Exceptions/LogicError.h"

namespace Tests
{
using namespace testing;

// I'm using Query both to prepare data and test :)

class QueryTests : public testing::Test
{
public:
	QueryTests()
		: databaseName("test_databases/Core_QueryTests.db"),
		  db(std::make_unique<Db::Database>(databaseName))
	{
		dropMainTable();
		createMainTable();
		fillMainTable();
	}

	void dropMainTable()
	{
		auto sql = "drop table if exists main";
		Db::Query(db.get(), sql).executeCommand();
	}

	void createMainTable()
	{
		auto createTableSql =
			"\n create table main("
			"\n     id int primary key not null,"
			"\n     first int,"
			"\n     second char(20),"
			"\n     third double"
			"\n )";

		Db::Query(db.get(), createTableSql).executeCommand();
	}

	void insertRow(int id, int first, const std::string& second, double third)
	{
		std::stringstream insertSql;

		// clang-format off
		insertSql <<
			"\n insert into main"
			"\n ("
			"\n     id,"
			"\n     first,"
			"\n     second,"
			"\n     third"
			"\n )"
			"\n values "
			"\n ("
			"\n     " << id << ","
			"\n     " << first << ","
			"\n     '" << second << "',"
			"\n     '" << third << "'"
			"\n )"
		;
		// clang-format on

		Db::Query(db.get(), insertSql.str()).executeCommand();
	}

	void fillMainTable()
	{
		insertRow(1, 100, "Sto", 1.1);
		insertRow(2, 1000, "Tysiąc", 1.2);
	}

	void validateThirdRow()
	{
		auto sql = "select * from main m where m.id=3";
		auto result = Db::Query(db.get(), sql).execute();

		validateRow(result.getFirstRow(), 3, 1000000, "Milijon", 1.3245);
	}

	void validateRow(
		const Db::Row* r, int id, int first, const std::string& second, double third)
	{
		EXPECT_THAT(r->get<int>("id"), Eq(id));
		EXPECT_THAT(r->get<int>("first"), Eq(first));
		EXPECT_THAT(r->get<std::string>("second"), Eq(second));
		EXPECT_THAT(r->get<double>("third"), Eq(third));
	}

	auto getInsertQuery()
	{
		return "\n insert into main"
			   "\n ("
			   "\n     id,"
			   "\n     first,"
			   "\n     second,"
			   "\n     third"
			   "\n )"
			   "\n values "
			   "\n ("
			   "\n     :id,"
			   "\n     :first,"
			   "\n     :second,"
			   "\n     :third"
			   "\n )";
	}

	std::string databaseName;
	std::unique_ptr<Db::Database> db;
};

// error handling

TEST_F(QueryTests, throws_logic_error_when_cannot_find_parameter)
{
	try
	{
		auto sql = "select * from main m where m.id = :id";
		auto query = Db::Query(db.get(), sql);
		query.setParam(":nonExistingParam", "");
		FAIL() << "Logic error about non existing parameter shoul be thrown";
	}
	catch (LogicError& err)
	{
		auto expectedMessage =
			std::string("Could not find parameter :nonExistingParam");

		ASSERT_THAT(err.what(), Eq(expectedMessage));
	}
}

TEST_F(QueryTests, throws_error_when_parameter_is_not_set)
{
	try
	{
		auto sql = "select * from main m where m.id = :id";
		auto query = Db::Query(db.get(), sql);
		query.executeCommand();

		FAIL() << "Logic error about unknown param shoul be thrown";
	}
	catch (const LogicError& err)
	{
		auto expectedMessage = std::string("Query: parameter :id is not set");

		ASSERT_THAT(err.what(), Eq(expectedMessage));
	}
}

// execute command
TEST_F(QueryTests, insert_row_without_using_parameters)
{
	auto insertSql =
		"\n insert into main"
		"\n ("
		"\n     id,"
		"\n     first,"
		"\n     second,"
		"\n     third"
		"\n )"
		"\n values "
		"\n ("
		"\n     3,"
		"\n     1000000,"
		"\n     'Milijon',"
		"\n     1.3245"
		"\n )";

	auto query = Db::Query(db.get(), insertSql);
	query.executeCommand();
	validateThirdRow();
}

TEST_F(QueryTests, insert_row_using_parameters)
{
	auto query = Db::Query(db.get(), getInsertQuery());
	query.setParam(":id", 3);
	query.setParam(":first", 1000000);
	query.setParam(":second", "Milijon");
	query.setParam(":third", 1.3245);
	query.executeCommand();

	validateThirdRow();
}

TEST_F(QueryTests, thros_logic_error_when_query_in_command_rerurns_value)
{
	try
	{
		auto sql = "select * from main m";
		auto query = Db::Query(db.get(), sql);
		query.executeCommand();

		FAIL() << "Logic error expected";
	}
	catch (const LogicError& err)
	{
		auto expected = "Db: Query returned a value while executing command";

		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(QueryTests, throws_error_on_incorrect_command_during_preparation)
{
	try
	{
		auto sql = "select * from main2 m";
		auto query = Db::Query(db.get(), sql);
		query.executeCommand();

		FAIL() << "Logic error expected";
	}
	catch (const LogicError& err)
	{
		auto expected = "Db: no such table: main2";

		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(QueryTests, throws_error_during_execution)
{
	try
	{
		// row with id = 1 already exists in database
		insertRow(1, 1, "aaaa", 1.5);
	}
	catch (const LogicError& err)
	{
		auto expected = "Db: UNIQUE constraint failed: main.id";
		ASSERT_STREQ(err.what(), expected);
	}
}

// execute
TEST_F(QueryTests, select_using_parameters)
{
	auto sql = "select * from main m where m.id = :id";
	auto query = Db::Query(db.get(), sql);
	query.setParam(":id", 2);
	auto dataset = query.execute();

	ASSERT_FALSE(dataset.empty());
	validateRow(dataset.getFirstRow(), 2, 1000, "Tysiąc", 1.2);
}

TEST_F(QueryTests, select_that_returns_empty_dataset)
{
	auto sql = "select * from main m where m.id = :id";
	auto query = Db::Query(db.get(), sql);
	query.setParam(":id", 1000); // some nonexisting index
	auto result = query.execute();

	EXPECT_TRUE(result.initialized());
	EXPECT_TRUE(result.empty());
}

TEST_F(QueryTests, select_multiple_rows)
{
	auto sql = "select * from main m order by m.id";
	auto query = Db::Query(db.get(), sql);
	auto dataset = query.execute();

	auto index{0};

	for (const auto& r : dataset)
	{
		if (index == 0)
			validateRow(&r, 1, 100, "Sto", 1.1);

		else if (index == 1)
			validateRow(&r, 2, 1000, "Tysiąc", 1.2);

		index++;
	}
}

TEST_F(QueryTests, selecting_null_values)
{
	auto insertSql =
		"\n insert into main"
		"\n ("
		"\n     id,"
		"\n     first"
		"\n )"
		"\n values "
		"\n ("
		"\n     3,"
		"\n     10"
		"\n )";

	Db::Query(db.get(), insertSql).executeCommand();

	auto sql = "select * from main m where m.id = :id";
	auto query = Db::Query(db.get(), sql);
	query.setParam(":id", 3);

	auto dataset = query.execute();
	auto row = dataset.getFirstRow();

	ASSERT_THAT(row->get<std::string>("second"), Eq(""));
}

} // namespace Tests