#include "HtCli/AppInit/InitDaoFactory.h"

#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/HabitDao.h"
#include "HT/Dao/RequirementDao.h"

namespace AppInit
{

template<typename T>
void registerDao(Dao::DaoFactory* factory, const std::string& name)
{
	factory->registerDao(name, [](Db::Database* db) -> Dao::UnknownDaoPtr
		{return std::make_shared<T>(db);});
}

std::unique_ptr<Dao::DaoFactory> initDaoFactory(Db::Database* db)
{
	auto daoFactory = std::make_unique<Dao::DaoFactory>();
	daoFactory->setDatabase(db);

	registerDao<Dao::HabitDefinitionDao>(daoFactory.get(), "habitDefinition");
	registerDao<Dao::HabitDao>(daoFactory.get(), "habit");
	registerDao<Dao::RequirementDao>(daoFactory.get(), "requirement");

	return daoFactory;
}

} // namespace AppInit
