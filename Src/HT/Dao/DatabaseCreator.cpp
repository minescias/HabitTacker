#include "HT/Dao/DatabaseCreator.h"

#include <Core/Database/Database.h>
#include <Core/Database/Query.h>

namespace
{
auto getCreateHabitDefinitionSql()
{
	return "\n create table habit_definition"
		   "\n ("
		   "\n 	id integer primary key autoincrement,"
		   "\n 	name varchar(40),"
		   "\n 	begin_date date not null"
		   "\n )";
}

auto getCreateHabitTable()
{
	return "\n create table habit"
		   "\n ("
		   "\n 	habit_id integer,"
		   "\n 	date date,"
		   "\n 	primary key(habit_id, date)"
		   "\n 	foreign key(habit_id) references habit_definition(id)"
		   "\n )";
}

auto getCreateRequirementTable()
{
	return R"sql(
		create table requirement
		(
			id integer primary key autoincrement,
			habit_id integer not null,
			begin_date date not null,
			end_date date,
			daily_target integer not null
		)
		)sql";
}

} // namespace

namespace Dao
{
DatabaseCreator::DatabaseCreator(const std::string& filename)
	: filename(filename)
{
}

std::unique_ptr<Db::Database> DatabaseCreator::createEmptyDatabase() const
{
	auto database = std::make_unique<Db::Database>(filename);

	createHabitDefinitionTable(database.get());
	createHabitTable(database.get());
	createRequirementTable(database.get());

	return database;
}

void DatabaseCreator::createHabitDefinitionTable(Db::Database* db) const
{
	Db::Query query(db, getCreateHabitDefinitionSql());
	query.executeCommand();
}

void DatabaseCreator::createHabitTable(Db::Database* db) const
{
	Db::Query query(db, getCreateHabitTable());
	query.executeCommand();
}

void DatabaseCreator::createRequirementTable(Db::Database* db) const
{
	Db::Query query(db, getCreateRequirementTable());
	query.executeCommand();
}

} // namespace Dao
