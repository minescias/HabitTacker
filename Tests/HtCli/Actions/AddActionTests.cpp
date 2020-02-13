#include <gmock/gmock.h>

#include <Core/DateTime/DateTimeGetter.h>

#include "CLI/App.hpp"

#include "HtCli/Actions/ActionError.h"
#include "HtCli/Actions/AddAction.h"

#include "Mocks/HT/Dao/HabitDefinitionDaoMock.h"
#include "Mocks/HT/Dao/RequirementDaoMock.h"
#include "Tests/HtCli/Tools/CliTestTools.h"
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

		addCommand.setDaoFactory(&factory);
		addCommand.setCliParameters(&app);
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
	Commands::AddCommand addCommand;
	CLI::App app;
};

TEST_F(AddActionTests, saves_habit_to_database)
{
	EXPECT_CALL(*daoMock, getDefinition("new habit name"))
		.WillOnce(Return(ByMove(Entity::HabitDefinitionEntityPtr())));

	EXPECT_CALL(*daoMock, saveDefinition(getDefinition()));
	EXPECT_CALL(*requirementDaoMock, save(getRequirement()));

	// minimum configuration that is required to add habit

	parseArguments(&app, {"add", "--name", "new habit name"});
	addCommand.execute();
}

TEST_F(AddActionTests, ensures_that_name_is_not_empty)
{
	parseAndThrowError(&app, {"add"}, "--name is required");
}

TEST_F(AddActionTests, throw_error_when_adding_habit_that_already_esists)
{
	EXPECT_CALL(*daoMock, getDefinition("new habit name"))
		.WillOnce(
			Return(ByMove(std::make_unique<Entity::HabitDefinitionEntity>())));

	try
	{
		parseArguments(&app, {"add", "-n", "new habit name"});
		addCommand.execute();
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

	parseArguments(&app, {"add", "-n", "new habit name", "-t", "32"});
	addCommand.execute();
}

} // namespace Tests
