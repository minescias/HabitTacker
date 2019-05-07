#ifndef __ACTION_H
#define __ACTION_H

#include "HT/Dao/DaoFactory.h"

namespace Actions
{

class IAction
{
public:
	virtual void setDaoFactory(Dao::DaoFactory* daoFactory) = 0;

	virtual ~IAction(){}
};

} // namespace Actions

#endif
