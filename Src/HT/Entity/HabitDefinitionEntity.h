#ifndef __HABIT_DEFINITION_ENTITY
#define __HABIT_DEFINITION_ENTITY

#include <memory>
#include <string>
#include <vector>

#include "Core/DateTime/Timestamp.h"

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

	void setBeginDate(Dt::Timestamp date);
	Dt::Timestamp getBeginDate() const;

private:
	int id;
	std::string name;
	Dt::Timestamp beginDate;
};

bool operator==(const HabitDefinitionEntity &a, const HabitDefinitionEntity &b);

using HabitDefinitionEntityPtr = std::unique_ptr<HabitDefinitionEntity>;
using HabitDefinitions = std::vector<HabitDefinitionEntityPtr>;

} // namespace Entity

#endif
