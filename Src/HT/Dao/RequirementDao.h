#ifndef __REQUIREMENT_DAO_H
#define __REQUIREMENT_DAO_H

#include <Core/Database/Database_fwd.h>

#include "HT/Dao/IRequirementDao.h"

namespace Dao
{
class RequirementDao : public IRequirementDao
{
public:
	RequirementDao(Db::Database* db);

	virtual void save(const Entity::Requirement& requirement) const;
	virtual std::unique_ptr<Entity::Requirement> read(int id) const;

private:
	Db::Database* db;
};

} // namespace Dao

#endif // __REQUIREMENTS_DAO_H
