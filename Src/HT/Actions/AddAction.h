#ifndef __ADD_ACTION_H
#define __ADD_ACTION_H

#include <string>

#include "HT/Actions/BaseAction.h"

namespace Actions
{

class AddAction : public BaseAction
{
public:
	AddAction() = default;

protected:
	void initValidator() final;
	void doExecute(const Cli::Parameters& parameters) final;
};

} // namespace Actions

#endif
