#include "HT/Actions/EditAction.h"

#include <Core/Cli/Validator.h>
#include "HT/Actions/ActionError.h"

namespace Actions
{

EditAction::EditAction()
{
}

void EditAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
    dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");
}

void EditAction::execute(const Cli::Parameters& parameters)
{
    validateParameters(parameters);

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

void EditAction::validateParameters(const Cli::Parameters& parameters)
{
    auto validator = Cli::Validator();
    validator.enableFilter();
    validator.addParam("name").type(Cli::ParamType::String);
    validator.validate(parameters);
}

} // namespace Actions
