#include <HtCli/Actions/AddAction.h>

#include <Core/DateTime/DateTimeGetter.h>

#include "HT/Dao/IHabitDefinitionDao.h"
#include "HT/Dao/IRequirementDao.h"
#include "HtCli/Actions/ActionError.h"

namespace Actions
{
using Dao::IHabitDefinitionDao;
using Dao::IRequirementDao;

void AddAction::initValidator()
{
	validator.addDefaultParameter()
		.requirement(Cli::RequirementLevel::Required)
		.errorMessage("No habit name specified");

	validator.addParam("target").type(Cli::ParamType::Integer);
}

void AddAction::doExecute(const Cli::Parameters& parameters)
{
	auto dao = daoFactory->createDao<IHabitDefinitionDao>("habitDefinition");
	auto requirementDao = daoFactory->createDao<IRequirementDao>("requirement");

	auto name = parameters.getDefaultParameter();
	auto existingDefinition = dao->getDefinition(name);
	if (existingDefinition)
		throw ActionError("Habit with name '" + name + "' already exists");

	auto newDefinition = Entity::HabitDefinitionEntity();
	newDefinition.setName(name);
	dao->saveDefinition(newDefinition);

	auto requirement = Entity::Requirement();
	requirement.setHabitId(1);
	requirement.setBeginDate(Dt::getCurrentDate());
	requirement.setEndDate(std::nullopt);
	requirement.setTarget(getTarget(parameters));
	requirementDao->save(requirement);
}

int AddAction::getTarget(const Cli::Parameters& parameters)
{
	auto target = parameters.getParameter("target");

	if (target.empty())
		return 1;
	else
		return stoi(target);
}

} // namespace Actions
