#ifndef __DAO_FACTORY_H
#define __DAO_FACTORY_H

#include "HT/Dao/UnknownDao.h"

#include <functional>
#include <map>
#include <string>

#include <Core/Database/Database.h>
#include <Core/Utils/Exceptions/LogicError.h>

namespace Dao
{

// pointer to a function that creates Dao
// using DaoCreatorFunc = Dao::UnknownDaoPtr (*)();
using DaoCreatorFunc = std::function<Dao::UnknownDaoPtr(Db::Database* db)>;

class DaoFactory
{
public:
	DaoFactory();

	void registerDao(const std::string& name, DaoCreatorFunc daoCreator);
	void setDatabase(Db::Database* db);

	template<typename T>
	std::unique_ptr<T> createDao(const std::string& daoName) const
	{
		if (!isDaoRegistered(daoName))
			throw LogicError("DaoFactory: " + daoName + " is not registered");

		auto unknownDaoPtr = registeredDaos.at(daoName)(db);
		auto daoPtr = dynamic_cast<T*>(unknownDaoPtr.release());

		if (daoPtr == nullptr)
		{
			throw LogicError("DaoFactory: "
				"trying to cast " + daoName + " to wrong type");
		}

		return std::unique_ptr<T>(daoPtr);
	}

private:
	bool isDaoRegistered(const std::string& daoName) const;

private:
	std::map<std::string, DaoCreatorFunc> registeredDaos;
	Db::Database* db;
};

} // namespace Dao

#endif // __DAO_FACTORY_H