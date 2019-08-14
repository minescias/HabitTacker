#ifndef __LIST_ACTION_H
#define __LIST_ACTION_H

#include "HT/Dao/IHabitDefinitionDao.h"
#include "HT/Actions/IAction.h"

namespace Actions
{

class ListAction : public IAction
{
public:
	ListAction();

	void setDaoFactory(Dao::DaoFactory* factory);
	void execute(const Cli::Parameters& parameters);

private:
	void validateParameters(const Cli::Parameters& parameters);
	void printHeader() const;

private:
	std::shared_ptr<Dao::IHabitDefinitionDao> dao;
};

} // namespace Actions

#endif
