#include "HtCli/Actions/EditAction.h"

#include "HtCli/Actions/ActionError.h"
#include "HT/Dao/HabitDefinitionDao.h"

namespace Actions
{

void EditAction::doExecute(const Cli::Parameters& parameters)
{
    auto dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
    auto habitId = parameters.getFilter();

    auto name = parameters.getParameter("name");
    if (name.empty())
        throw ActionError("Nothing to change");

    auto defintion = dao->getDefinition(std::stoi(habitId));
    if (!defintion)
        throw ActionError("Habit with id = " + habitId + " does not exist");

    defintion->setName(name);
    dao->updateDefinition(*defintion);
}

void EditAction::initValidator()
{
    validator.addFilter().requirement(Cli::RequirementLevel::Required);
    validator.addParam("name").type(Cli::ParamType::String);
}

} // namespace Actions
