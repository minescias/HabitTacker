#include <gmock/gmock.h>

#include <filesystem>
#include <iomanip>
#include <memory>

#include <Core/DateTime/DateTimeGetter.h>
#include <Core/DateTime/DateTime.h>

#include "HT/Dao/DatabaseCreator.h"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/HabitDao.h"

namespace
{

auto filename = "test_habitDao.db"; //"test_DgQADg8ICA0.db";

} // namespace

namespace Tests
{

using namespace testing;
namespace fs = std::filesystem;

class HabitDaoTests : public testing::Test
{
public:
	HabitDaoTests()
	{
		fs::remove(filename);
		db = Dao::DatabaseCreator{filename}.createEmptyDatabase();
		definitionDao = std::make_unique<Dao::HabitDefinitionDao>(db.get());
		habitDao = std::make_unique<Dao::HabitDao>(db.get());
	}

	void addDefinition(const std::string& name)
	{
		Entity::HabitDefinitionEntity definition;
		definition.setName(name);

		definitionDao->saveDefinition(definition);
	}

	auto addHabit(int habitId, Dt::Timestamp date)
	{
		auto habit = Entity::HabitEntity();
		habit.setHabitId(habitId);
		habit.setDate(date);

		habitDao->saveHabit(habit);
		return habit;
	}

	std::unique_ptr<Db::Database> db;
	std::unique_ptr<Dao::IHabitDefinitionDao> definitionDao;
	std::unique_ptr<Dao::IHabitDao> habitDao;
};

TEST_F(HabitDaoTests, readAndWriteTest)
{
	addDefinition("Some definition");

	auto writtenHabit = Entity::HabitEntity();
	writtenHabit.setHabitId(1);
	writtenHabit.setDate(Dt::getCurrentDate());

	habitDao->saveHabit(writtenHabit);
	auto readHabits = habitDao->getHabitsById(1);

	ASSERT_THAT(readHabits.size(), Eq(1));
	EXPECT_THAT(*readHabits[0], Eq(writtenHabit));
}

TEST_F(HabitDaoTests, checksIfHabitIsSetForDay)
{
	addDefinition("Some definition");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	ASSERT_FALSE(habitDao->checkIfHabitIsSetForDay(habit));
	habitDao->saveHabit(habit);
	ASSERT_TRUE(habitDao->checkIfHabitIsSetForDay(habit));
}

TEST_F(HabitDaoTests, getsHabitsFromLastTwoWeeks)
{
	auto today = Dt::getCurrentDate();

	addDefinition("Some definition");
	addDefinition("Some definition2");

	// included data
	auto h1 = addHabit(1, today);
	auto h2 = addHabit(1, Dt::DateTime{today}.addDays(-2).unixTime());
	auto h3 = addHabit(2, Dt::DateTime{today}.addDays(-1).unixTime());
	auto h4 = addHabit(2, Dt::DateTime{today}.addDays(-2).unixTime());
	auto h5 = addHabit(2, Dt::DateTime{today}.addDays(-10).unixTime());
	auto h6 = addHabit(2, Dt::DateTime{today}.addDays(-13).unixTime());

	// excluded data over 14 days
	auto h7 = addHabit(1, Dt::DateTime{today}.addDays(-14).unixTime());
	auto h8 = addHabit(2, Dt::DateTime{today}.addDays(-15).unixTime());

	auto habits = habitDao->getHabitsFromLastTwoWeeks(today);

	ASSERT_THAT(habits.size(), Eq(6));
	EXPECT_THAT(*habits[0], Eq(h1));
	EXPECT_THAT(*habits[1], Eq(h2));
	EXPECT_THAT(*habits[2], Eq(h3));
	EXPECT_THAT(*habits[3], Eq(h4));
	EXPECT_THAT(*habits[4], Eq(h5));
	EXPECT_THAT(*habits[5], Eq(h6));
}

} // namespace Tests
