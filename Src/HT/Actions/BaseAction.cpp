#include "HT/Actions/BaseAction.h"

namespace Actions
{

void BaseAction::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	this->daoFactory = daoFactory;
}

void BaseAction::execute(const Cli::Parameters& parameters)
{
	initValidator();
	validator.validate(parameters);

	doExecute(parameters);
}

} // namespace Actions
