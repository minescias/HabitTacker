#ifndef __BASE_ACTION_H
#define __BASE_ACTION_H


#include <Core/Cli/Validator.h>
#include <HT/Actions/IAction.h>

namespace Actions
{

class BaseAction : public IAction
{
public:
	BaseAction() = default;
	virtual ~BaseAction() = default;

	void setDaoFactory(Dao::DaoFactory* daoFactory) final;
	void execute(const Cli::Parameters& parameters) final;

protected:
	virtual void initValidator() = 0;
	virtual void doExecute(const Cli::Parameters& parameters) = 0;

protected:
	Dao::DaoFactory* daoFactory;
	Cli::Validator validator;
};

} // namespace Actions

#endif // __BASE_ACTION_H
