#ifndef __I_HABIT_DEFINITION_DAO
#define __I_HABIT_DEFINITION_DAO

#include "HT/Entity/HabitDefinitionEntity.h"

namespace Dao
{

class IHabitDefinitionDao
{
public:
	virtual void saveDefinition(const Entity::HabitDefinitionEntity entity) = 0;
	virtual Entity::HabitDefinitionEntityPtr getDefinition(int definitionId) = 0;
};

} //namespace Dao

#endif
