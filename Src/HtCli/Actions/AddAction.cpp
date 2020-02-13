#include <HtCli/Actions/AddAction.h>

#include <CLI/App.hpp>

#include <Core/DateTime/DateTimeGetter.h>

#include "HT/Dao/IHabitDefinitionDao.h"
#include "HT/Dao/IRequirementDao.h"
#include "HtCli/Actions/ActionError.h"

namespace Commands
{
using Dao::IHabitDefinitionDao;
using Dao::IRequirementDao;

void AddCommand::setCliParameters(CLI::App* app)
{
	auto command = app->add_subcommand("add", "Creates new h");
	command->add_option("-n,--name", name, "New habit name")->required();
	command->add_option("-t,--target", target, "Daily target")->default_val(1);
}

void AddCommand::execute()
{
	auto dao = daoFactory->createDao<IHabitDefinitionDao>("habitDefinition");
	auto requirementDao = daoFactory->createDao<IRequirementDao>("requirement");

	auto existingDefinition = dao->getDefinition(name);
	if (existingDefinition)
	{
		throw Actions::ActionError(
			"Habit with name '" + name + "' already exists");
	}

	auto newDefinition = Entity::HabitDefinitionEntity();
	newDefinition.setName(name);
	dao->saveDefinition(newDefinition);

	auto requirement = Entity::Requirement();
	requirement.setHabitId(1);
	requirement.setBeginDate(Dt::getCurrentDate());
	requirement.setEndDate(std::nullopt);
	requirement.setTarget(target);
	requirementDao->save(requirement);
}

} // namespace Commands
