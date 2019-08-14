#ifndef __EDIT_ACTION_H
#define __EDIT_ACTION_H

#include "HT/Actions/IAction.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class EditAction : public IAction
{
public:
	EditAction();

	void setDaoFactory(Dao::DaoFactory* daoFactory);
	void execute(const Cli::Parameters& parameters);

private:
	void validateParameters(const Cli::Parameters& parameters);

private:
	std::shared_ptr<Dao::IHabitDefinitionDao> dao;
};

} // namespace Actions

#endif // __EDIT_ACTION_H
