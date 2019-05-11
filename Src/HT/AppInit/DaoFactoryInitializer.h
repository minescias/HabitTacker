#ifndef __DAO_FACTORY_INITIALIZER
#define __DAO_FACTORY_INITIALIZER

#include "HT/Dao/DaoFactory.h"

std::unique_ptr<Dao::DaoFactory> initDaoFactory(Db::Database* db);

#endif
