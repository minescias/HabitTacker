#include <gmock/gmock.h>

#include <Libraries/SQLite/sqlite3.h>
#include <filesystem>

namespace Tests
{
using namespace testing;
namespace fs = std::filesystem;

class Sqlite_returnIdOfInsertedObject : public testing::Test
{
public:
	Sqlite_returnIdOfInsertedObject()
		: databaseName("test_files/Lib_Sqlite_insertedRowId.db"){};

	~Sqlite_returnIdOfInsertedObject()
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

	void createTestTable()
	{
		auto sql = R"sql(
			create table TestTable
			(
				id integer primary key autoincrement,
				descr varchar(40) not null
			)
			)sql";

		executeQuery(sql);
	}
	void checkDbStatus(const std::string& command, int status, int expectedStatus = SQLITE_OK)
	{
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

	std::string errorMessage;
	const char* databaseName;
	sqlite3* dbHandler;
};

TEST_F(Sqlite_returnIdOfInsertedObject, first)
{
	fs::remove(databaseName);
	openDatabase();
	executeQuery("PRAGMA foreign_keys = ON");
	createTestTable();

	auto insertSql = R"sql(
		insert into TestTable (id, descr) values (12, 'aaaaaaaa')
	)sql";

	executeQuery(insertSql);

	EXPECT_THAT(errorMessage, Eq(""));
	EXPECT_THAT(sqlite3_last_insert_rowid(dbHandler), Eq(12));
}

} // namespace Tests
