#ifndef __UNKNOWN_DAO
#define __UNKNOWN_DAO

#include <memory>

namespace Dao
{

class UnknownDao
{
public:
	virtual ~UnknownDao(){};
};

using UnknownDaoPtr = std::unique_ptr<UnknownDao>;

} // namespace Dao

#endif // __UNKNOWN_DAO
