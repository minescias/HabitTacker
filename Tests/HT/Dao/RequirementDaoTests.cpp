#include <gmock/gmock.h>

#include <filesystem>

#include <Core/DateTime/AddDays.h>
#include <Core/DateTime/DateTimeGetter.h>
#include <Core/Exceptions/LogicError.h>

#include "HT/Dao/DatabaseCreator.h"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/RequirementDao.h"
#include "HT/Entity/Requirement.h"

namespace
{
auto testDatabaseName = "test_databases/HT_RequirementDaoTests.db";
}

namespace Tests
{
using namespace date;
using namespace testing;

using Entity::Requirement;
namespace fs = std::filesystem;

class RequirementDaoTests : public testing::Test
{
public:
	RequirementDaoTests()
	{
		fs::remove(testDatabaseName);
		db = Dao::DatabaseCreator{testDatabaseName}.createEmptyDatabase();
		dao = std::make_unique<Dao::RequirementDao>(db.get());
		definitionDao = std::make_unique<Dao::HabitDefinitionDao>(db.get());
	};

	int createHabitDefinition() const
	{
		Entity::HabitDefinitionEntity definition;
		definition.setName("def");

		definitionDao->saveDefinition(definition);
		return 1; // na pustej bazie id będzie zawsze równe 1. Planuję dodać
				  // zwracanie id po zapisie do bazy
	}

	void compareEntities(const Requirement& actual, const Requirement& expected)
	{
		EXPECT_THAT(actual.getId(), Eq(expected.getId()));
		EXPECT_THAT(actual.getHabitId(), Eq(expected.getHabitId()));
		EXPECT_THAT(actual.getBeginDate(), Eq(expected.getBeginDate()));
		EXPECT_THAT(actual.getEndDate(), Eq(expected.getEndDate()));
		EXPECT_THAT(actual.getTarget(), Eq(expected.getTarget()));
	}

	std::unique_ptr<Db::Database> db;
	std::unique_ptr<Dao::IRequirementDao> dao;
	std::unique_ptr<Dao::IHabitDefinitionDao> definitionDao;
};

TEST_F(RequirementDaoTests, save_and_read_tests)
{
	createHabitDefinition();

	Entity::Requirement req;
	req.setId(1); // ponownie opieram się na założeniu, że baza jest pusta
	req.setHabitId(1);
	req.setTarget(10);
	req.setBeginDate(2019_y / November / 20);
	req.setEndDate(std::nullopt);

	dao->save(req);

	auto readReq = dao->read(1);
	compareEntities(*readReq, req);
}

TEST_F(RequirementDaoTests, throws_error_on_unknown_habit_id)
{
	// test of requirement foreign key constraint
	Entity::Requirement req;
	req.setId(1);
	req.setHabitId(12321); // some id that doesn't exist
	req.setTarget(10);
	req.setBeginDate(2019_y / November / 20);
	req.setEndDate(2019_y / December / 30);

	try
	{
		dao->save(req);
		FAIL();
	}
	catch (LogicError& err)
	{
		auto expected = "Db: FOREIGN KEY constraint failed";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(RequirementDaoTests, read_returns_empty_pointer_when_no_requirements_found)
{
	auto req = dao->read(1234);
	ASSERT_FALSE(req);
}

TEST_F(RequirementDaoTests, gets_current_tasrget)
{
	createHabitDefinition();

	Entity::Requirement req;
	req.setHabitId(1);
	
	req.setTarget(10);
	req.setBeginDate(Dt::addDays(Dt::getCurrentDate(), -20));
	req.setEndDate(Dt::addDays(Dt::getCurrentDate(), -11));
	dao->save(req);

	req.setTarget(20);
	req.setBeginDate(Dt::addDays(Dt::getCurrentDate(), -10));
	req.setEndDate(Dt::addDays(Dt::getCurrentDate(), 10));
	dao->save(req);

	req.setTarget(30);
	req.setBeginDate(Dt::addDays(Dt::getCurrentDate(), 11));
	req.setEndDate(std::nullopt);
	dao->save(req);

	auto currentTarget = dao->getCurrentTarget(1);
	auto expectedTarget = 30;

	ASSERT_THAT(currentTarget, Eq(expectedTarget));
}

} // namespace Tests
