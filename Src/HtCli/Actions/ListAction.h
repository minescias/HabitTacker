#ifndef __LIST_ACTION_H
#define __LIST_ACTION_H

#include "HtCli/Actions/BaseAction.h"
#include "HT/Dao/IHabitDefinitionDao.h"

namespace Actions
{

class ListAction : public BaseAction
{
public:
	ListAction() = default;

protected:
	void initValidator() final;
	void doExecute(const Cli::Parameters& parameters) final;

private:
	void printHeader() const;
};

} // namespace Actions

#endif
