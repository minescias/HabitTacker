#include "HT/Dao/HabitDefinitionDao.h"

#include <Core/Database/Database.h>
#include <Core/Database/Dataset.h>
#include <Core/Database/Query.h>

namespace Dao
{

using Entity::HabitDefinitionEntity;
using Entity::HabitDefinitionEntityPtr;

HabitDefinitionDao::HabitDefinitionDao(Db::Database* db)
	:db(db)
{

}

HabitDefinitionDao::~HabitDefinitionDao()
{
}

void HabitDefinitionDao::saveDefinition(const HabitDefinitionEntity& entity)
{
	std::string sql =
		"\n insert into habit_definition"
		"\n ("
		"\n 	name"
		"\n )"
		"\n values"
		"\n ("
		"\n 	:name"
		"\n )";

	Db::Query query(db, sql);
	query.setParam(":name", entity.getName());
	query.execute();
}

HabitDefinitionEntityPtr HabitDefinitionDao::getDefinition(int definitionId)
{
	std::string sql =
		"\n select "
		"\n 	id,"
		"\n 	name"
		"\n from"
		"\n 	habit_definition h"
		"\n where"
		"\n 	h.id = :id";

	Db::Query query(db, sql);
	query.setParam(":id", definitionId);
	auto dataset = query.execute();

	if (dataset->empty())
		return HabitDefinitionEntityPtr();

	auto result = std::make_unique<HabitDefinitionEntity>();
	result->setId(dataset->getAs<int>("id"));
	result->setName(dataset->getAs<std::string>("name"));

	return result;
}

} // namespace Dao
