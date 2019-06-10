#include <gmock/gmock.h>

#include <filesystem>
#include <memory>

#include "Core/DateTime/DateTimeGetter.h"

#include "HT/Dao/DatabaseCreator.h"
#include "HT/Dao/HabitDefinitionDao.h"

namespace Tests
{

using namespace testing;
namespace fs = std::filesystem;
const char* filename = "test_DgQADg8ICA0.db";

class HabitDefinitionDaoTests : public testing::Test
{
public:
	HabitDefinitionDaoTests()
	{
		fs::remove(filename);
		db = Dao::DatabaseCreator{filename}.createEmptyDatabase();
		dao = std::make_unique<Dao::HabitDefinitionDao>(db.get());
	}

	auto getDefinition(int id, const std::string& name)
	{
		auto definition = std::make_unique<Entity::HabitDefinitionEntity>();
		definition->setId(id);
		definition->setName(name);
		definition->setBeginDate(Dt::getCurrentDate());

		return  definition;
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

TEST_F(HabitDefinitionDaoTests, reads_empty_pointer_when_definition_not_found)
{
	auto readDefiniton = dao->getDefinition(1000);
	ASSERT_FALSE(readDefiniton);
}

TEST_F(HabitDefinitionDaoTests, saves_and_reads_by_id)
{
	addDefinition("Example definition");
	auto readDefiniton = dao->getDefinition(1);

	ASSERT_TRUE(readDefiniton);
	EXPECT_THAT(readDefiniton->getId(), Eq(1));
	EXPECT_THAT(readDefiniton->getName(), Eq("Example definition"));
	EXPECT_THAT(readDefiniton->getBeginDate(), Eq(Dt::getCurrentDate()));
}

TEST_F(HabitDefinitionDaoTests, read_definition_by_name)
{
	addDefinition("Example definition");
	auto readDefiniton = dao->getDefinition("Example definition");

	ASSERT_TRUE(readDefiniton);
	EXPECT_THAT(readDefiniton->getId(), Eq(1));
	EXPECT_THAT(readDefiniton->getName(), Eq("Example definition"));
	EXPECT_THAT(readDefiniton->getBeginDate(), Eq(Dt::getCurrentDate()));
}

TEST_F(HabitDefinitionDaoTests, updates_definition_when_it_already_exist)
{
	addDefinition("Example defiiiiiiinitions"); // creates definition with id=1

	auto definition = Entity::HabitDefinitionEntity();
	definition.setId(1);
	definition.setName("Example definition");

	dao->updateDefinition(definition);

	auto readDefinition = dao->getDefinition(1);
	ASSERT_THAT(readDefinition->getName(), definition.getName());
}

TEST_F(HabitDefinitionDaoTests, reads_all_definitions)
{
	addDefinition("Example definition");
	addDefinition("Example definition2");
	addDefinition("Example definition3");

	auto definitions = dao->getDefinitions();

	ASSERT_THAT(definitions.size(), Eq(3));
	EXPECT_THAT(*definitions[0], Eq(*getDefinition(1, "Example definition")));
	EXPECT_THAT(*definitions[1], Eq(*getDefinition(2, "Example definition2")));
	EXPECT_THAT(*definitions[2], Eq(*getDefinition(3, "Example definition3")));
}

} // namespace Tests
