#include "HT/Dao/HabitDefinitionDao.h"

#include <Core/Database/Database.h>
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
	query.executeCommand();
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
	query.executeCommand();
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

	if (dataset.empty())
		return HabitDefinitionEntityPtr();

	auto row = dataset.getFirstRow();
	auto result = std::make_unique<HabitDefinitionEntity>();
	result->setId(row->get<int>("id"));
	result->setName(row->get<std::string>("name"));
	result->setBeginDate(row->get<Dt::Timestamp>("begin_date"));

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

	if (dataset.empty())
		return HabitDefinitionEntityPtr();

	auto row = dataset.getFirstRow();
	auto result = std::make_unique<HabitDefinitionEntity>();
	result->setId(row->get<int>("id"));
	result->setName(row->get<std::string>("name"));
	result->setBeginDate(row->get<Dt::Timestamp>("begin_date"));

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

	// while(dataset->next())
	for (const auto& row: dataset)
	{
		result.emplace_back(std::make_unique<Entity::HabitDefinitionEntity>());
		result.back()->setId(row.get<int>("id"));
		result.back()->setName(row.get<std::string>("name"));
		result.back()->setBeginDate(row.get<Dt::Timestamp>("begin_date"));
	}

	return result;
}

} // namespace Dao
