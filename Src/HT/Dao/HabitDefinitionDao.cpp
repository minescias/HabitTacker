#include "HT/Dao/HabitDefinitionDao.h"

#include <Core/Database/Database.h>
#include <Core/Database/Dataset.h>
#include <Core/Database/Query.h>
#include <Core/DateTime/DateTimeGetter.h>

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

void HabitDefinitionDao::saveDefinition(const HabitDefinitionEntity& entity) const
{
	std::string sql =
		"\n insert into habit_definition"
		"\n ("
		"\n 	name,"
		"\n 	begin_date"
		"\n )"
		"\n values"
		"\n ("
		"\n 	:name,"
		"\n 	:date"
		"\n )";

	Db::Query query(db, sql);
	query.setParam(":name", entity.getName());
	query.setParam(":date", Dt::getCurrentDate());
	query.execute();
}

void HabitDefinitionDao::updateDefinition(const HabitDefinitionEntity& entity) const
{
	std::string sql =
		"\n update"
		"\n 	habit_definition"
		"\n set"
		"\n 	name = :name"
		"\n where"
		"\n 	id = :id";

	Db::Query query(db, sql);
	query.setParam(":name", entity.getName());
	query.setParam(":id", entity.getId());
	query.execute();
}

HabitDefinitionEntityPtr HabitDefinitionDao::getDefinition(int definitionId) const
{
	std::string sql =
		"\n select "
		"\n 	id,"
		"\n 	name,"
		"\n 	begin_date"
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
	result->setBeginDate(dataset->getAs<Dt::Timestamp>("begin_date"));

	return result;
}

Entity::HabitDefinitionEntityPtr HabitDefinitionDao::getDefinition(
	const std::string& name) const
{
	std::string sql =
		"\n select "
		"\n 	id,"
		"\n 	name,"
		"\n 	begin_date"
		"\n from"
		"\n 	habit_definition h"
		"\n where"
		"\n 	h.name = :name";

	Db::Query query(db, sql);
	query.setParam(":name", name);
	auto dataset = query.execute();

	if (dataset->empty())
		return HabitDefinitionEntityPtr();

	auto result = std::make_unique<HabitDefinitionEntity>();
	result->setId(dataset->getAs<int>("id"));
	result->setName(dataset->getAs<std::string>("name"));
	result->setBeginDate(dataset->getAs<Dt::Timestamp>("begin_date"));

	return result;
}

Entity::HabitDefinitions HabitDefinitionDao::getDefinitions() const
{
	auto result = Entity::HabitDefinitions();

	std::string sql =
		"\n select "
		"\n 	id,"
		"\n 	name,"
		"\n 	begin_date"
		"\n from"
		"\n 	habit_definition h";

	Db::Query query(db, sql);
	auto dataset = query.execute();

	while(dataset->next())
	{
		result.emplace_back(std::make_unique<Entity::HabitDefinitionEntity>());
		result.back()->setId(dataset->getAs<int>("id"));
		result.back()->setName(dataset->getAs<std::string>("name"));
		result.back()->setBeginDate(dataset->getAs<Dt::Timestamp>("begin_date"));
	}

	return result;
}

} // namespace Dao
