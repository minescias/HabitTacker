#ifndef __REQUIREMENT_H
#define __REQUIREMENT_H

#include <optional>

#include <Core/DateTime/Date.h>

namespace Entity
{
class Requirement
{
public:
	Requirement();

	void setId(int id);
	int getId() const;

	void setHabitId(int habitId);
	int getHabitId() const;

	void setBeginDate(Dt::Date beginDate);
	Dt::Date getBeginDate() const;

	void setEndDate(std::optional<Dt::Date> beginDate);
	std::optional<Dt::Date> getEndDate() const;

	void setTarget(int target);
	int getTarget() const;

	bool operator==(const Requirement& rhs) const;

private:
	int id;
	int habitId;
	Dt::Date beginDate;
	std::optional<Dt::Date> endDate;
	int target;
};

} // namespace Entity

#endif // __REQUIREMENT_H
