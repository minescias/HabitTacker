#include "HT/Dao/DatabaseCreator.h"

#include <Core/Database/Database.h>
#include <Core/Database/Dataset.h>
#include <Core/Database/Query.h>

namespace
{

std::string getCreateHabitDefinitionSql()
{
	return
		"\n create table habit_definition"
		"\n ("
		"\n     id integer primary key autoincrement,"
		"\n     name varchar(40)"
		"\n )";
}

} // namespace

namespace Dao
{

DatabaseCreator::DatabaseCreator(const std::string& filename)
{
	database = std::make_unique<Db::Database>(filename);
}

void DatabaseCreator::createHabitDefinitionTable()
{
	Db::Query query(database.get(), getCreateHabitDefinitionSql());
	query.execute();
}

} // namespace


