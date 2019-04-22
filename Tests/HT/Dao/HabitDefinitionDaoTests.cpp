#include <gmock/gmock.h>

#include <filesystem>
#include <memory>

#include <HT/Dao/DatabaseCreator.h>
#include "HT/Dao/HabitDefinitionDao.h"

namespace
{

using namespace testing;
namespace fs = std::filesystem;
const char* filename = "test_DgQADg8ICA0.db";

} // namespace

class HabitDefinitionDaoTests : public testing::Test
{
public:
	HabitDefinitionDaoTests()
	{
		fs::remove(filename);
		Dao::DatabaseCreator(filename).createHabitDefinitionTable();
		db = std::make_unique<Db::Database>(filename);
		dao = std::make_unique<Dao::HabitDefinitionDao>(db.get());
	}

	void addDefinition(const std::string& name)
	{
		Entity::HabitDefinitionEntity definition;
		definition.setName(name);

		dao->saveDefinition(definition);
	}

	std::unique_ptr<Db::Database> db;
	std::unique_ptr<Dao::IHabitDefinitionDao> dao;
};

TEST_F(HabitDefinitionDaoTests, readsEmptyPointerWhenDefinitionNotFound)
{
	auto readDefiniton = dao->getDefinition(1000);
	ASSERT_FALSE(readDefiniton);
}

TEST_F(HabitDefinitionDaoTests, saveAndReadByIdTest)
{
	addDefinition("Example definition");
	auto readDefiniton = dao->getDefinition(1);

	ASSERT_TRUE(readDefiniton);
	EXPECT_THAT(readDefiniton->getId(), Eq(1));
	EXPECT_STREQ(readDefiniton->getName().c_str(), "Example definition");
}
