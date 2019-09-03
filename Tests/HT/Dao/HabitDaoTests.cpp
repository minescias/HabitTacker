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

	void compareHabits(const Entity::HabitEntity& actual,
		const Entity::HabitEntity& expected) const
	{
		EXPECT_THAT(actual.getHabitId(), Eq(expected.getHabitId()));
		EXPECT_THAT(actual.getDate(), Eq(expected.getDate()));
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
	compareHabits(*readHabits[0], writtenHabit);
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
	addHabit(1, Dt::DateTime{today}.addDays(-14).unixTime());
	addHabit(2, Dt::DateTime{today}.addDays(-15).unixTime());

	auto habits = habitDao->getHabitsFromLastTwoWeeks(today);

	ASSERT_THAT(habits.size(), Eq(6));
	compareHabits(*habits[0], h1);
	compareHabits(*habits[1], h2);
	compareHabits(*habits[2], h3);
	compareHabits(*habits[3], h4);
	compareHabits(*habits[4], h5);
	compareHabits(*habits[5], h6);
}

TEST_F(HabitDaoTests, deleteHabitTests)
{
	addDefinition("Some definition");

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(Dt::getCurrentDate());

	habitDao->saveHabit(habit);
	ASSERT_TRUE(habitDao->checkIfHabitIsSetForDay(habit));
	habitDao->deleteHabit(habit);
	ASSERT_FALSE(habitDao->checkIfHabitIsSetForDay(habit));
}

} // namespace Tests
