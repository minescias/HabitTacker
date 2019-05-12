#include "HT/Dao/HabitDao.h"

#include <Core/Database/Database.h>
#include <Core/Database/Dataset.h>
#include <Core/Database/Query.h>
#include <Core/DateTime/Timestamp.h>

namespace Dao
{

using Entity::HabitEntity;
using Entity::HabitEntityPtr;

HabitDao::HabitDao(Db::Database* db)
	: db(db)
{
}

void HabitDao::saveHabit(const HabitEntity& habit)
{
	std::string sql =
		"\n insert into habit"
		"\n ("
		"\n 	habit_id,"
		"\n 	date"
		"\n )"
		"\n values "
		"\n ("
		"\n 	:habit_id,"
		"\n 	:date"
		"\n )";

	Db::Query query(db, sql);
	query.setParam(":habit_id", habit.getHabitId());
	query.setParam(":date", habit.getDate());
	query.execute();
}

std::vector<HabitEntityPtr> HabitDao::getHabitsById(int id)
{
	auto result = std::vector<HabitEntityPtr>();

	std::string sql =
		"\n select"
		"\n 	h.date"
		"\n from"
		"\n 	habit h"
		"\n where"
		"\n 	h.habit_id = :habit_id";

	Db::Query query(db, sql);
	query.setParam(":habit_id", id);
	auto queryResult = query.execute();

	// ale buła :)
	if (queryResult->next())
	{
		auto& habit = result.emplace_back(std::make_unique<HabitEntity>());
		habit->setHabitId(id);
		habit->setDate(queryResult->getAs<Dt::Timestamp>("date"));
	}

	return result;
}

bool HabitDao::checkIfHabitIsSetForDay(const HabitEntity& habit)
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

	if (queryResult->empty())
		return false;
	else
		return true;
}

std::vector<HabitEntityPtr> HabitDao::getHabitsFromLastTwoWeeks(
	Dt::Timestamp date)
{
	auto result = std::vector<HabitEntityPtr>();
	auto secondsInDay{86400};	// 86400 = 24 * 60 * 60

	std::string sql =
		"\n select"
		"\n 	h.habit_id, "
		"\n 	h.date"
		"\n from"
		"\n 	habit h"
		"\n where"
		"\n 	h.date between :date_from and :date_to";

	Db::Query query(db, sql);
	query.setParam(":date_from", date - secondsInDay * 13);
	query.setParam(":date_to", date);
	query.execute();

	auto queryResult = query.execute();

	while (queryResult->next())
	{
		auto& habit = result.emplace_back(std::make_unique<HabitEntity>());
		habit->setHabitId(queryResult->getAs<int>("habit_id"));
		habit->setDate(queryResult->getAs<Dt::Timestamp>("date"));
	}

	return result;
}

} // namespace Dao
