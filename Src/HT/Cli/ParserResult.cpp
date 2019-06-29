#include "HT/Cli/ParserResult.h"

namespace Cli
{

void ParserResult::setFilter(const std::string& filter)
{
	this->filter = filter;
}

std::string ParserResult::getFilter() const
{
	return filter;
}

void ParserResult::setFlag(const std::string& flagName)
{
	flags.emplace(flagName);
}

bool ParserResult::getFlag(const std::string& flagName) const
{
	return flags.find(flagName) != flags.end();
}

} // namespace Cli




