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

	std::unique_ptr<Db::Database> createEmptyDatabase() const;

private:
	void createHabitDefinitionTable(Db::Database* db) const;
	void createHabitTable(Db::Database* db) const;

private:
	std::string filename;
};

} // namespace Dao

#endif
