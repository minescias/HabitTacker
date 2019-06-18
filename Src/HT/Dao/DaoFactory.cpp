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

Dao::UnknownDaoPtr DaoFactory::getDaoAsUnknown(const std::string& daoName) const
{
		// if (!isDaoRegistered(daoName))
		// 	throw LogicError("DaoFactory: " + daoName + " is not registered");

		return registeredDaos.at(daoName)(db);
		// auto daoPtr = dynamic_cast<T*>(unknownDaoPtr.release());

		// if (daoPtr == nullptr)
		// {
		// 	throw LogicError("DaoFactory: "
		// 		"trying to cast " + daoName + " to wrong type");
		// }

		// return std::shared_ptr<T>();
}

bool DaoFactory::isDaoRegistered(const std::string& daoName) const
{
	// c++20 - std::map::contains(...)
	return registeredDaos.find(daoName) != registeredDaos.end();
}

} // namespace Dao
