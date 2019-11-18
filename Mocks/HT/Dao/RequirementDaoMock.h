#ifndef __REQUIREMENT_DAO_MOCK_H
#define __REQUIREMENT_DAO_MOCK_H

#include <gmock/gmock.h>

#include "HT/Dao/IRequirementDao.h"

namespace Mocks
{
class RequirementDaoMock : public Dao::IRequirementDao
{
public:
	MOCK_CONST_METHOD1(save, void(const Entity::Requirement& requirement));
	MOCK_CONST_METHOD1(read, std::unique_ptr<Entity::Requirement>(int id));
	MOCK_CONST_METHOD1(getCurrentTarget, int(int habitId));
};

} // namespace Mocks

#endif // __REQUIREMENT_DAO_MOCK_H
