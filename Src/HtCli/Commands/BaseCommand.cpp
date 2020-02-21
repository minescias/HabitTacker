#include "HtCli/Commands/BaseCommand.h"

namespace Commands
{

void BaseCommand::setDaoFactory(Dao::DaoFactory* daoFactory)
{
	this->daoFactory = daoFactory;
}

} // namespace Actions
