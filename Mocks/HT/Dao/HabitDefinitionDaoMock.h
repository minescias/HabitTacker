#ifndef __HABIT_DEFINITION_DAO_MOCK_H
#define __HABIT_DEFINITION_DAO_MOCK_H

#include <gmock/gmock.h>

#include "HT/Dao/IHabitDefinitionDao.h"

namespace Mocks
{

class HabitDefinitionDaoMock : public Dao::IHabitDefinitionDao
{
public:
	MOCK_CONST_METHOD1(saveDefinition, void(const Entity::HabitDefinitionEntity& entity));
	MOCK_CONST_METHOD1(getDefinition, Entity::HabitDefinitionEntityPtr (int definitionId));
	MOCK_CONST_METHOD0(getDefinitions, Entity::HabitDefinitions());
};

} // namespace Mocks

#endif
