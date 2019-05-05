#ifndef __DAO_FACTORY_H
#define __DAO_FACTORY_H

#include "HT/Dao/UnknownDao.h"

#include <functional>
#include <map>
#include <string>

namespace Dao
{

// pointer to a function that creates Dao
// using DaoCreatorFunc = Dao::UnknownDaoPtr (*)();
using DaoCreatorFunc = std::function<Dao::UnknownDaoPtr()>;

class DaoFactory
{
public:
	DaoFactory();

	void registerDao(const std::string& name, DaoCreatorFunc daoCreator);

	template<typename T>
	std::unique_ptr<T> createDao(const std::string& daoName)
	{
		auto daoPtr = registeredDaos.at(daoName)();
		return std::unique_ptr<T>(dynamic_cast<T*>(daoPtr.release()));
	}

private:
	std::map<std::string, DaoCreatorFunc> registeredDaos;
};

} // namespace Dao

#endif // __DAO_FACTORY_H