#include <gmock/gmock.h>

#include <Core/Database/Database.h>
#include <Core/Database/Query.h>
#include <Core/DateTime/Date.h>

// Podstawowe typy zmiennych są już testowane w ramach QueryTests. W tym pliku
// powinny się znajdować testy bardziej skomplikowanych typów

namespace Tests
{
using namespace date;
using namespace testing;

class ParametersTest : public testing::Test
{
public:
	ParametersTest()
		: db(std::make_unique<Db::Database>("tests/ParametestTests.db"))
	{
		dropTestTables();
		createDateTestsTable();
		createOptionalTestsTable();
	};

	void dropTestTables()
	{
		auto sql = "drop table if exists date_tests";
		Db::Query(db.get(), sql).executeCommand();

		sql = "drop table if exists optional_tests";
		Db::Query(db.get(), sql).executeCommand();
	}

	void createDateTestsTable()
	{
		auto sql =
			"\n create table date_tests("
			"\n 	id int primary key not null,"
			"\n 	value date"
			"\n )";

		Db::Query(db.get(), sql).executeCommand();
	}

	void createOptionalTestsTable()
	{
		auto sql =
			"\n create table optional_tests("
			"\n 	id int primary key not null,"
			"\n 	opt_value int,"
			"\n 	opt_text int"
			"\n )";

		Db::Query(db.get(), sql).executeCommand();
	}

	auto getInsertDateSql() const
	{
		return "\n insert into date_tests"
			   "\n ("
			   "\n 	id,"
			   "\n 	value"
			   "\n )"
			   "\n values"
			   "\n ("
			   "\n 	:id,"
			   "\n 	:date"
			   "\n )";
	}

	auto getInsertOptionalSql() const
	{
		return "\n insert into optional_tests"
			   "\n ("
			   "\n 	id,"
			   "\n 	opt_value,"
			   "\n 	opt_text"
			   "\n )"
			   "\n values"
			   "\n ("
			   "\n 	:id,"
			   "\n 	:opt_value,"
			   "\n 	:opt_text"
			   "\n )";
	}

	auto getSelectDateSql() const
	{
		return "select value from date_tests dt where dt.id = :id";
	}

	auto getSelectOptionalSql() const
	{
		return "select opt_value, opt_text from optional_tests ot where ot.id = :id";
	}


	std::unique_ptr<Db::Database> db;
};

TEST_F(ParametersTest, insert_date)
{
	auto query = Db::Query(db.get(), getInsertDateSql());
	query.setParam(":id", 1);
	query.setParam(":date", 2019_y / September / 20);
	query.executeCommand();

	auto selectQuery = Db::Query(db.get(), getSelectDateSql());
	selectQuery.setParam(":id", 1);
	auto result = selectQuery.execute();
	auto row = result.getFirstRow();

	ASSERT_THAT(row->get<int>("value"), Eq(18159));
}

TEST_F(ParametersTest, select_date)
{
	auto query = Db::Query(db.get(), getInsertDateSql());
	query.setParam(":id", 1);
	query.setParam(":date", 18160);
	query.executeCommand();

	auto selectQuery = Db::Query(db.get(), getSelectDateSql());
	selectQuery.setParam(":id", 1);
	auto result = selectQuery.execute();
	auto row = result.getFirstRow();

	ASSERT_THAT(row->get<Dt::Date>("value"), Eq(2019_y / September / 21));
}

TEST_F(ParametersTest, save_null_value_to_database)
{
	auto query = Db::Query(db.get(), getInsertOptionalSql());
	query.setParam(":id", 1);
	query.setParam(":opt_value", Db::ParamType::Null);
	query.setParam(":opt_text", Db::ParamType::Null);
	query.executeCommand();

	auto selectQuery = Db::Query(db.get(), getSelectOptionalSql());
	selectQuery.setParam(":id", 1);

	auto result = selectQuery.execute();
	auto row = result.getFirstRow();

	EXPECT_THAT(row->get<std::string>("opt_value"), Eq(""));
	EXPECT_THAT(row->get<std::string>("opt_text"), Eq(""));
}

} // namespace Tests
