#include "HT/Dao/RequirementDao.h"

#include <Core/Database/Query.h>

namespace Dao
{
RequirementDao::RequirementDao(Db::Database* db) : db(db)
{
}

void RequirementDao::save(const Entity::Requirement& requirement) const
{
	auto sql = R"sql(
		insert into requirement
		(
			habit_id,
			begin_date,
			end_date,
			daily_target
		)
		values
		(
			:habit_id,
			:begin_date,
			:end_date,
			:daily_target
		)
		)sql";

	Db::Query query(db, sql);
	query.setParam(":habit_id", requirement.getHabitId());
	query.setParam(":begin_date", requirement.getBeginDate());
	query.setParam(":end_date", requirement.getEndDate());
	query.setParam(":daily_target", requirement.getTarget());
	query.executeCommand();
}

std::unique_ptr<Entity::Requirement> RequirementDao::read(int id) const
{
	auto sql = R"sql(
		select
			habit_id,
			begin_date,
			end_date,
			daily_target
		from
			requirement r
		where
			r.id = :id
		)sql";

	Db::Query query(db, sql);
	query.setParam(":id", id);
	auto dataset = query.execute();

	if (dataset.empty())
		return nullptr;

	auto row = dataset.getFirstRow();
	auto result = std::make_unique<Entity::Requirement>();

	result->setId(id);
	result->setHabitId(row->get<int>("habit_id"));
	result->setBeginDate(row->get<Dt::Date>("begin_date"));
	result->setEndDate(row->get<Dt::Date>("end_date"));
	result->setTarget(row->get<int>("daily_target"));
	return result;
}

int RequirementDao::getCurrentTarget(int habitId) const
{
	auto sql = R"sql(
		select
			daily_target
		from
			requirement r
		where
			r.habit_id = :habit_id
		)sql";

	Db::Query query(db, sql);
	query.setParam(":habit_id", habitId);
	auto dataset = query.execute();

	auto row = dataset.getFirstRow();
	return row->get<int>("daily_target");
}

} // namespace Dao
