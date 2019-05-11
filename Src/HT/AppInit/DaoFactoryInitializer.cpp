#include "HT/AppInit/DaoFactoryInitializer.h"

#include "HT/Dao/HabitDefinitionDao.h"
#include "HT/Dao/HabitDao.h"

std::unique_ptr<Dao::DaoFactory> initDaoFactory(Db::Database* db)
{
	auto daoFactory = std::make_unique<Dao::DaoFactory>();
	daoFactory->setDatabase(db);

	daoFactory->registerDao("habitDefinition", [](Db::Database* db){
		return std::make_unique<Dao::HabitDefinitionDao>(db);});

	daoFactory->registerDao("habit", [](Db::Database* db){
		return std::make_unique<Dao::HabitDao>(db);});

	return daoFactory;
}

