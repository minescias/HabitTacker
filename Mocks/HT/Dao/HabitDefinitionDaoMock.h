#ifndef __HABIT_DEFINITION_DAO_MOCK_H
#define __HABIT_DEFINITION_DAO_MOCK_H

#include <gmock/gmock.h>

#include <Core/Database/Database.h>

#include "HT/Dao/IHabitDefinitionDao.h"

namespace Mocks
{

class HabitDefinitionDaoMock : public Dao::IHabitDefinitionDao
{
public:
	HabitDefinitionDaoMock(Db::Database* db = nullptr){}

	MOCK_CONST_METHOD1(saveDefinition, void(const Entity::HabitDefinitionEntity& entity));
	MOCK_CONST_METHOD1(updateDefinition, void(const Entity::HabitDefinitionEntity& entity));
	MOCK_CONST_METHOD1(getDefinition, Entity::HabitDefinitionEntityPtr (int definitionId));
	MOCK_CONST_METHOD1(getDefinition, Entity::HabitDefinitionEntityPtr (const std::string& name));
	MOCK_CONST_METHOD0(getDefinitions, Entity::HabitDefinitions());
};

} // namespace Mocks

#endif
