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
	void execute(const Cli::ParserResult& parserResult);

private:
	void printHeader() const;

private:
	std::unique_ptr<Dao::IHabitDefinitionDao> dao;
};

} // namespace Actions

#endif
