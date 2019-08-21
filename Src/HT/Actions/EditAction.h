#ifndef __EDIT_ACTION_H
#define __EDIT_ACTION_H

#include "HT/Actions/BaseAction.h"

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
