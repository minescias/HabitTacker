#ifndef __INIT_DAO_FACTORY_H
#define __INIT_DAO_FACTORY_H

#include "HT/Dao/DaoFactory.h"

namespace AppInit
{

std::unique_ptr<Dao::DaoFactory> initDaoFactory(Db::Database* db);

} // namespace AppInit

#endif //__INIT_DAO_FACTORY_H
