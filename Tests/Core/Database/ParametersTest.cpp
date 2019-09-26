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
		dropDateTable();
		createTestsTable();
	};

	void dropDateTable()
	{
		auto sql = "drop table if exists date_tests";
		Db::Query(db.get(), sql).executeCommand();
	}

	void createTestsTable()
	{
		auto sql =
			"\n create table date_tests("
			"\n 	id int primary key not null,"
			"\n 	value date)";

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

	auto getSelectDateSql() const
	{
		return "select value from date_tests dt where dt.id = :id";
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

} // namespace Tests
