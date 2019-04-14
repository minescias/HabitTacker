#ifndef __INIT_ACTION
#define __INIT_ACTION

#include <string>

namespace Actions
{

class InitAction
{
public:
	InitAction();
	void execute(const std::string& filename) const;
};

} // namespace Actions

#endif
