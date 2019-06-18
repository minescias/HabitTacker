#ifndef __REGISTER_AND_GET_DAO_MOCK_H
#define __REGISTER_AND_GET_DAO_MOCK_H

#include "HT/Dao/DaoFactory.h"

namespace Tests
{

template<typename T>
auto registerAndGetDaoMock(Dao::DaoFactory* factory, const std::string& name)
{
	factory->registerDao(name, [](Db::Database* db) -> Dao::UnknownDaoPtr
		{return std::make_shared<T>();});

	return factory->createDao<T>(name);
}

} // namespace Tests

#endif // __REGISTER_AND_GET_DAO_MOCK_H
