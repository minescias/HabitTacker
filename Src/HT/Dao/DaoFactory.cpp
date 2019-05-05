#include "HT/Dao/DaoFactory.h"

namespace Dao
{

DaoFactory::DaoFactory()
{
}

void DaoFactory::registerDao(const std::string& name, DaoCreatorFunc daoCreator)
{
	registeredDaos.emplace(name, daoCreator);
}

} // namespace Dao
