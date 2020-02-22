#include <gmock/gmock.h>

#include <filesystem>
#include <iostream>

#include "sqlite/sqlite3.h"

namespace Tests
{
using namespace testing;

namespace fs = std::filesystem;

class SqliteForeignKeyTests : public testing::Test
{
public:
	SqliteForeignKeyTests()
		: databaseName("test_files/Lib_SqliteUniqueTests.db"){};

	~SqliteForeignKeyTests()
	{
		closeDatabse();
	}

	void openDatabase()
	{
		auto dbStatus = sqlite3_open(databaseName, &dbHandler);
		checkDbStatus("sqlite3_open", dbStatus);
	}

	void closeDatabse()
	{
		auto dbStatus = sqlite3_close(dbHandler);
		checkDbStatus("sqlite3_close", dbStatus);
	}

	void createFirstTestTable()
	{
		auto sql = R"sql(
			create table firstTable
			(
				id integer primary key,
				descr varchar(40) not null
			)
			)sql";

		executeQuery(sql);
	}

	void createSecondTestTable()
	{
		auto sql = R"sql(
			create table secondTable
			(
				id integer primary key,
				first_id integer not null,
				some_value integer not null,
				foreign key(first_id) references firstTable(id)
			)
			)sql";

		executeQuery(sql);
	}

	void insertIntoFirst(int id, const std::string desc)
	{
		std::stringstream sql;
		sql << "\n insert into firstTable (id, descr)"
			   "\n values ( "
			<< id << ", '" << desc << "')";
		executeQuery(sql.str());
	}

	void insertIntoSecond(int id, int firstId, int someValue)
	{
		std::stringstream sql;
		sql << "\n insert into secondTable (id, first_id, some_value)"
			   "\n values( "
			<< id << ", " << firstId << ", " << someValue << ")";
		executeQuery(sql.str());
	}

	void checkDbStatus(const std::string& command, int status, int expectedStatus = SQLITE_OK)
	{
		// std::stringstream msg;
		// msg << command << ": " << sqlite3_errmsg(dbHandler)
		// 	<< "(err code:" << status << ")\n";
		// 	std::cout << msg.str();

		if (status != expectedStatus)
			errorMessage = sqlite3_errmsg(dbHandler);
	}

	void executeQuery(const std::string& sql)
	{
		// std::cout << "executing \n" << sql << "\n";

		sqlite3_stmt* statement;

		auto dbStatus = sqlite3_prepare_v2(
			dbHandler, sql.c_str(), sql.size(), &statement, nullptr);
		checkDbStatus("sqlite3_prepare_v2", dbStatus);

		dbStatus = sqlite3_step(statement);
		checkDbStatus("sqlite3_step", dbStatus, SQLITE_DONE);

		sqlite3_finalize(statement);
		checkDbStatus("sqlite3_finalize", dbStatus, SQLITE_DONE);
	}

public:
	std::string errorMessage;
	const char* databaseName;
	sqlite3* dbHandler;
};

TEST_F(SqliteForeignKeyTests, unique_constraint_test)
{
	fs::remove(databaseName);
	openDatabase();
	executeQuery("PRAGMA foreign_keys = ON");
	createFirstTestTable();
	createSecondTestTable();

	insertIntoFirst(1, "aaa");
	insertIntoSecond(1, 1, 1); // ok, first with id = 1 exists in database

	EXPECT_TRUE(errorMessage.empty());
	insertIntoSecond(2, 2, 2);
	EXPECT_THAT(errorMessage, Eq("FOREIGN KEY constraint failed"));
}

} // namespace Tests
