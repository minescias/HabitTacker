#ifndef __EDIT_ACTION_H
#define __EDIT_ACTION_H

#include "HtCli/Actions/BaseAction.h"

namespace Actions
{

class EditAction : public BaseAction
{
public:
	EditAction() = default;

protected:
	void initValidator() final;
	void doExecute(const Cli::Parameters& parameters);
};

} // namespace Actions

#endif // __EDIT_ACTION_H
