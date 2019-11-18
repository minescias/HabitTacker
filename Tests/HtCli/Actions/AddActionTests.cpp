#include <gmock/gmock.h>

#include <Core/DateTime/DateTimeGetter.h>

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/AddAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Mocks/HT/Dao/RequirementDaoMock.h"
#include "Tests/Tools/RegisterAndGetDaoMock.h"

namespace Tests
{
using namespace testing;

class AddActionTests : public testing::Test
{
public:
	AddActionTests()
	{
		daoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
			&factory, "habitDefinition");

		requirementDaoMock = registerAndGetDaoMock<Mocks::RequirementDaoMock>(
			&factory, "requirement");

		addAction.setDaoFactory(&factory);
		pr.setCommandName("add");
	}

	auto getDefinition()
	{
		Entity::HabitDefinitionEntity definition;
		definition.setName("new habit name");
		return definition;
	}

	auto getRequirement()
	{
		Entity::Requirement req;
		req.setBeginDate(Dt::getCurrentDate());
		req.setEndDate(std::nullopt);
		req.setTarget(1); // default target value
		req.setHabitId(1);
		return req;
	}

	std::shared_ptr<Mocks::HabitDefinitionDaoMock> daoMock;
	std::shared_ptr<Mocks::RequirementDaoMock> requirementDaoMock;
	Dao::DaoFactory factory;
	Actions::AddAction addAction;
	Cli::Parameters pr;
};

TEST_F(AddActionTests, saves_habit_to_database)
{
	EXPECT_CALL(*daoMock, getDefinition("new habit name"))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	EXPECT_CALL(*daoMock, saveDefinition(getDefinition()));
	EXPECT_CALL(*requirementDaoMock, save(getRequirement()));

	// minimum configuration that is required to add habit
	pr.setDefaultParameter("new habit name");
	addAction.execute(pr);
}

TEST_F(AddActionTests, ensures_that_name_is_not_empty)
{
	try
	{
		addAction.execute(pr);
		FAIL() << "Expected runtime error";
	}
	catch (RuntimeError& err)
	{
		auto expected{"No habit name specified"};
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(AddActionTests, throw_error_when_adding_habit_that_already_esists)
{
	EXPECT_CALL(*daoMock, getDefinition("new habit name"))
		.WillOnce(
			Return(ByMove(std::make_unique<Entity::HabitDefinitionEntity>())));

	try
	{
		pr.setDefaultParameter("new habit name");
		addAction.execute(pr);
		FAIL() << "Action error expected";
	}
	catch (Actions::ActionError& err)
	{
		auto expected{"Habit with name 'new habit name' already exists"};
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(AddActionTests, allows_to_add_target_as_optional_parameter)
{
	auto requirement = getRequirement();
	requirement.setTarget(32);

	EXPECT_CALL(*daoMock, getDefinition("new habit name"))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	EXPECT_CALL(*daoMock, saveDefinition(getDefinition()));
	EXPECT_CALL(*requirementDaoMock, save(requirement));

	// minimum configuration that is required to add habit
	pr.setParameter("target", "32");
	pr.setDefaultParameter("new habit name");
	addAction.execute(pr);
}

} // namespace Tests
