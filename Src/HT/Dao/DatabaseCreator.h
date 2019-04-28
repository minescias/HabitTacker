#ifndef __DATABASE_CREATOR
#define __DATABASE_CREATOR

#include <memory>
#include <string>

#include <Core/Database/Database.h>

namespace Dao
{

class DatabaseCreator
{
public:
	DatabaseCreator(const std::string& filename);

	void createHabitDefinitionTable() const;
	void createHabitTable() const;

private:
	std::unique_ptr<Db::Database> database;
};

} // namespace Dao

#endif
