#ifndef __I_REQUIREMENT_DAO_H
#define __I_REQUIREMENT_DAO_H

#include <Core/Dao/UnknownDao.h>

#include "HT/Entity/Requirement.h"

namespace Dao
{
class IRequirementDao : public UnknownDao
{
public:
	virtual void save(const Entity::Requirement& requirement) const = 0;
	virtual std::unique_ptr<Entity::Requirement> read(int id) const = 0;
	virtual int getCurrentTarget(int habitId) const = 0;

	virtual ~IRequirementDao()
	{
	}
};

} // namespace Dao

#endif // __I_REQUIREMENTS_DAO_H
