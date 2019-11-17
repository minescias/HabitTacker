#include <gmock/gmock.h>

#include <filesystem>

#include "HT/Dao/DatabaseCreator.h"
#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/RequirementDao.h"
#include "HT/Entity/Requirement.h"

namespace
{
auto testDatabaseName = "test_databases/HT_RequirementDaoTests";
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
	Entity::Requirement req;
	req.setId(1); // opieram się na założeniu, że baza jest pusta
	req.setHabitId(createHabitDefinition());
	req.setTarget(10);
	req.setBeginDate(2019_y / November / 20);
	req.setEndDate(2019_y / December / 30);

	dao->save(req);

	auto readReq = dao->read(1);
	compareEntities(*readReq, req);
}

} // namespace Tests
