#ifndef __HABIT_DEFINITION_ENTITY
#define __HABIT_DEFINITION_ENTITY

#include <memory>
#include <string>

namespace Entity
{

class HabitDefinitionEntity
{
public:
	HabitDefinitionEntity();

	void setId(int id);
	int getId() const;

	void setName(const std::string& name);
	std::string getName() const;

private:
	int id;
	std::string name;
};

using HabitDefinitionEntityPtr = std::unique_ptr<HabitDefinitionEntity>;

} // namespace Entity

#endif
