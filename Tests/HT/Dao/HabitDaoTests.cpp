#include <gmock/gmock.h>

#include <ctime>
#include <filesystem>
#include <memory>
#include <iostream>
#include <iomanip>

#include "HT/Dao/DatabaseCreator.h"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/HabitDao.h"

namespace Tests
{

using namespace testing;
namespace fs = std::filesystem;

const char* filename = "test_habitDao.db"; //"test_DgQADg8ICA0.db";

class HabitDaoTests : public testing::Test
{
public:
	HabitDaoTests()
	{
		fs::remove(filename);
		auto creator = Dao::DatabaseCreator(filename);
		creator.createHabitDefinitionTable();
		creator.createHabitTable();

		db = std::make_unique<Db::Database>(filename);
		definitionDao = std::make_unique<Dao::HabitDefinitionDao>(db.get());
		habitDao = std::make_unique<Dao::HabitDao>(db.get());
	}

	void addDefinition(const std::string& name)
	{
		Entity::HabitDefinitionEntity definition;
		definition.setName(name);

		definitionDao->saveDefinition(definition);
	}

	auto addHabit(int habitId, time_t date)
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

	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto writtenHabit = Entity::HabitEntity();
	writtenHabit.setHabitId(1);
	writtenHabit.setDate(today);

	habitDao->saveHabit(writtenHabit);
	auto readHabits = habitDao->getHabitsById(1);

	ASSERT_THAT(readHabits.size(), Eq(1));
	EXPECT_THAT(*readHabits[0], Eq(writtenHabit));
}

TEST_F(HabitDaoTests, checksIfHabitIsSetForDay)
{
	addDefinition("Some definition");
	auto today = time(nullptr);
	today -= (today % 86400); // 86400 = 24 * 60 * 60

	auto habit = Entity::HabitEntity();
	habit.setHabitId(1);
	habit.setDate(today);

	ASSERT_FALSE(habitDao->checkIfHabitIsSetForDay(habit));
	habitDao->saveHabit(habit);
	ASSERT_TRUE(habitDao->checkIfHabitIsSetForDay(habit));
}

TEST_F(HabitDaoTests, getsHabitsFromLastTwoWeeks)
{
	auto today = time(nullptr);
	auto secondsInDay{86400};	// 86400 = 24 * 60 * 60
	today -= (today % secondsInDay);

	addDefinition("Some definition");
	addDefinition("Some definition2");

	// included data
	auto h1 = addHabit(1, today);
	auto h2 = addHabit(1, today - secondsInDay * 2);
	auto h3 = addHabit(2, today - secondsInDay * 1);
	auto h4 = addHabit(2, today - secondsInDay * 2);
	auto h5 = addHabit(2, today - secondsInDay * 10);
	auto h6 = addHabit(2, today - secondsInDay * 14);

	// excluded data over 14 days
	auto h7 = addHabit(1, today - secondsInDay * 15);
	auto h8 = addHabit(2, today - secondsInDay * 16);

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