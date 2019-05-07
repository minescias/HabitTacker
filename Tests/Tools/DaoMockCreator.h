#ifndef __DAO_MOCK_CREATOR
#define __DAO_MOCK_CREATOR

#include "HT/Dao/DaoFactory.h"

namespace Tests
{

// nie mogę użyć tej wersji ponieważ release jest metodą nie constową a z
// jakiegoś powodu nie mogę używać constowych metod w lambdzie :(

// template<typename T>
// Dao::DaoCreatorFunc createDaoMock(std::unique_ptr<T> daoPtr)
// {
// 	return [&daoPtr2 = std::move(daoPtr)]() -> Dao::UnknownDaoPtr
// 	{
// 		auto unknownDaoPtr = dynamic_cast<Dao::UnknownDao*>(daoPtr2.release());
// 		return std::unique_ptr<Dao::UnknownDao>(unknownDaoPtr);
// 	};
// }

template<typename T>
Dao::DaoCreatorFunc createDaoMock(T* daoPtr)
{
	return [daoPtr](Db::Database* db) -> Dao::UnknownDaoPtr
	{
		auto unknownDaoPtr = dynamic_cast<Dao::UnknownDao*>(daoPtr);
		return Dao::UnknownDaoPtr(unknownDaoPtr);
	};
}

} // namespace Tests

#endif // __DAO_MOCK_CREATOR
