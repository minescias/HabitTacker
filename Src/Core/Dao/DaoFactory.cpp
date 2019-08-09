#include "Core/Dao/DaoFactory.h"

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
	createdDaos.emplace(name, UnknownDaoPtr());
}

void DaoFactory::setDatabase(Db::Database* db)
{
	this->db = db;
}

Dao::UnknownDaoPtr DaoFactory::getDaoAsUnknown(const std::string& daoName)
{
	if (!isDaoRegistered(daoName))
		throw LogicError("DaoFactory: " + daoName + " is not registered");

	auto dao = createdDaos.at(daoName).lock();

	if (!dao)
	{
		dao = registeredDaos.at(daoName)(db);
		createdDaos.at(daoName) =  dao;
	}

	return dao;
}

bool DaoFactory::isDaoRegistered(const std::string& daoName) const
{
	// c++20 - std::map::contains(...)
	return registeredDaos.find(daoName) != registeredDaos.end();
}

} // namespace Dao
