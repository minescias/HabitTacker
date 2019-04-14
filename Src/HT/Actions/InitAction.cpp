#include "HT/Actions/InitAction.h"

#include <filesystem>

#include "HT/Actions/ActionError.h"
#include "HT/Dao/DatabaseCreator.h"

namespace Actions
{

InitAction::InitAction()
{
}

void InitAction::execute(const std::string& filename) const
{
	if (filename.empty())
		throw ActionError("No filename specified");

	if (std::filesystem::exists(filename))
		throw ActionError(std::string("File ") + filename + " already exists");

	Dao::DatabaseCreator creator(filename);
	creator.createHabitDefinitionTable();
}

} // namespace Actions
