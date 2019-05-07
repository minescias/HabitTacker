#include "HT/Dao/DaoFactory.h"

namespace Dao
{

DaoFactory::DaoFactory()
	: db(nullptr)
{
}

void DaoFactory::registerDao(const std::string& name, DaoCreatorFunc daoCreator)
{
	if (isDaoRegistered(name))
		throw LogicError("DaoFactory: " + name + " was already registered");

	registeredDaos.emplace(name, daoCreator);
}

void DaoFactory::setDatabase(Db::Database* db)
{
	this->db = db;
}

bool DaoFactory::isDaoRegistered(const std::string& daoName) const
{
	// c++20 - std::map::contains(...)
	return registeredDaos.find(daoName) != registeredDaos.end();
}

} // namespace Dao
