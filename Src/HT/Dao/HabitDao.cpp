#include "HT/Dao/HabitDao.h"

#include <Core/Database/Database.h>
#include <Core/Database/Query.h>
#include <Core/DateTime/Operators.h>

namespace Dao
{
using Entity::HabitEntity;
using Entity::HabitEntityPtr;

HabitDao::HabitDao(Db::Database* db) : db(db)
{
}

void HabitDao::saveHabit(const HabitEntity& habit) const
{
	auto sql = R"sql(
		insert into habit
		(
			habit_id,
			date,
			result
		)
		values 
		(
			:habit_id,
			:date,
			:result
		)
		)sql";

	Db::Query query(db, sql);
	query.setParam(":habit_id", habit.getHabitId());
	query.setParam(":date", habit.getDate());
	query.setParam(":result", habit.getResult());
	query.executeCommand();
}

void HabitDao::deleteHabit(const Entity::HabitEntity& habit) const
{
	auto sql =
		"\n delete from "
		"\n 	habit"
		"\n where"
		"\n 	habit_id = :habit_id"
		"\n 	and date = :date";

	Db::Query query(db, sql);
	query.setParam(":habit_id", habit.getHabitId());
	query.setParam(":date", habit.getDate());
	query.executeCommand();
}

std::vector<HabitEntityPtr> HabitDao::getHabitsById(int id) const
{
	auto result = std::vector<HabitEntityPtr>();

	auto sql = R"sql(
		select
			h.date,
			h.result
		from
			habit h
		where
			h.habit_id = :habit_id
		)sql";

	Db::Query query(db, sql);
	query.setParam(":habit_id", id);
	auto queryResult = query.execute();

	for (const auto& row : queryResult)
	{
		auto& habit = result.emplace_back(std::make_unique<HabitEntity>());
		habit->setHabitId(id);
		habit->setDate(row.get<Dt::Date>("date"));
		habit->setResult(row.get<int>("result"));
	}

	return result;
}

bool HabitDao::checkIfHabitIsSetForDay(const HabitEntity& habit) const
{
	std::string sql =
		"\n select"
		"\n 	1"
		"\n from"
		"\n 	habit h"
		"\n where"
		"\n 	h.habit_id = :habit_id"
		"\n 	and h.date = :date";

	Db::Query query(db, sql);
	query.setParam(":habit_id", habit.getHabitId());
	query.setParam(":date", habit.getDate());
	auto queryResult = query.execute();

	if (queryResult.empty())
		return false;

	else
		return true;
}

std::vector<Entity::HabitEntityPtr> HabitDao::getHabits(
	int definitionId, Dt::Date beginDate, Dt::Date endDate) const
{
	auto sql = R"sql(
		select
			h.date,
			h.result
		from
			habit h
		where
			h.date between :date_from and :date_to 
			and h.habit_id = :habit_id
		)sql";

	Db::Query query(db, sql);
	query.setParam(":date_from", beginDate);
	query.setParam(":date_to", endDate);
	query.setParam(":habit_id", definitionId);

	auto queryResult = query.execute();
	auto result = std::vector<HabitEntityPtr>();

	for (const auto& row : queryResult)
	{
		auto& habit = result.emplace_back(std::make_unique<HabitEntity>());
		habit->setHabitId(definitionId);
		habit->setDate(row.get<Dt::Date>("date"));
		habit->setResult(row.get<int>("result"));
	}

	return result;
}

} // namespace Dao
