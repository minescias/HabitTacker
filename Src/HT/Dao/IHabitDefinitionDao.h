#ifndef __I_HABIT_DEFINITION_DAO
#define __I_HABIT_DEFINITION_DAO

#include <vector>

#include "Core/Dao/UnknownDao.h"
#include "HT/Entity/HabitDefinitionEntity.h"

namespace Dao
{

class IHabitDefinitionDao : public UnknownDao
{
public:
	~IHabitDefinitionDao(){}

	virtual void saveDefinition(const Entity::HabitDefinitionEntity& entity) const = 0;
	virtual void updateDefinition(const Entity::HabitDefinitionEntity& entity) const = 0;
	virtual Entity::HabitDefinitionEntityPtr getDefinition(int definitionId) const = 0;
	virtual Entity::HabitDefinitionEntityPtr getDefinition(const std::string& name) const = 0;
	virtual Entity::HabitDefinitions getDefinitions() const = 0;
};

} //namespace Dao

#endif
