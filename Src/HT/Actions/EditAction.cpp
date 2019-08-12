#include "HT/Actions/EditAction.h"

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

void EditAction::execute(const Cli::Parameters& parserResult)
{
    auto habitId = parserResult.getFilter();
    if (habitId.empty())
        throw ActionError("No filter specified");

    auto name = parserResult.getParameter("name");
    if (name.empty())
        throw ActionError("Nothing to change");

    auto defintion = dao->getDefinition(std::stoi(habitId));
    if (!defintion)
        throw ActionError("Habit with id = " + habitId + " does not exist");

    defintion->setName(name);
    dao->updateDefinition(*defintion);
}

} // namespace Actions
