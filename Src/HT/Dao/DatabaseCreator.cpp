#include "HT/Dao/DatabaseCreator.h"

#include <Core/Database/Database.h>
#include <Core/Database/Dataset.h>
#include <Core/Database/Query.h>

namespace
{

auto getCreateHabitDefinitionSql()
{
	return
		"\n create table habit_definition"
		"\n ("
		"\n     id integer primary key autoincrement,"
		"\n     name varchar(40)"
		"\n )";
}

auto getCreateHabitTable()
{
	return
		"\n create table habit"
		"\n ("
		"\n 	habit_id integer,"
		"\n 	date date,"
		"\n 	result boolean not null,"
		"\n 	primary key(habit_id, date)"
		"\n 	foreign key(habit_id) references habit_definition(id)"
		"\n )";
}

} // namespace

namespace Dao
{

DatabaseCreator::DatabaseCreator(const std::string& filename)
{
	database = std::make_unique<Db::Database>(filename);
}

void DatabaseCreator::createHabitDefinitionTable() const
{
	Db::Query query(database.get(), getCreateHabitDefinitionSql());
	query.execute();
}

void DatabaseCreator::createHabitTable() const
{
	Db::Query query(database.get(), getCreateHabitTable());
	query.execute();
}

} // namespace


