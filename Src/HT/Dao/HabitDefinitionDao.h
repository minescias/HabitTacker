#ifndef __HABIT_DEFINITION_DAO
#define __HABIT_DEFINITION_DAO

#include <Core/Database/Database_fwd.h>

#include "HT/Dao/IHabitDefinitionDao.h"

namespace Dao
{

class HabitDefinitionDao : public IHabitDefinitionDao
{
public:
	HabitDefinitionDao(Db::Database* db);
	virtual ~HabitDefinitionDao();

	void saveDefinition(const Entity::HabitDefinitionEntity& entity) const;
	void updateDefinition(const Entity::HabitDefinitionEntity& entity) const;

	Entity::HabitDefinitionEntityPtr getDefinition(int definitionId) const;
	Entity::HabitDefinitionEntityPtr getDefinition(const std::string& name) const;
	Entity::HabitDefinitions getDefinitions() const;

private:
	Db::Database* db;
};

} //namespace Dao

#endif
