#ifndef __DAO_FACTORY_H
#define __DAO_FACTORY_H


#include <functional>
#include <map>
#include <string>

#include "Core/Dao/UnknownDao.h"
#include <Core/Database/Database.h>
#include <Core/Exceptions/LogicError.h>

namespace Dao
{

using DaoCreatorFunc = std::function<Dao::UnknownDaoPtr(Db::Database* db)>;

class DaoFactory
{
public:
	DaoFactory();

	void registerDao(const std::string& name, DaoCreatorFunc daoCreator);
	void setDatabase(Db::Database* db);

	template<typename T>
	auto createDao(const std::string& daoName)
	{
		auto dao = std::dynamic_pointer_cast<T>(getDaoAsUnknown(daoName));

		if (dao != nullptr)
			return dao;

		throw LogicError("DaoFactory: "
			"trying to cast " + daoName + " to wrong type");
	}

private:
	Dao::UnknownDaoPtr getDaoAsUnknown(const std::string& daoName);
	bool isDaoRegistered(const std::string& daoName) const;

private:
	std::map<std::string, DaoCreatorFunc> registeredDaos;
	std::map<std::string, std::weak_ptr<UnknownDao>> createdDaos;
	Db::Database* db;
};

} // namespace Dao

#endif // __DAO_FACTORY_H
