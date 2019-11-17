#ifndef __REQUIREMENT_H
#define __REQUIREMENT_H

#include <Core/DateTime/Date.h>

namespace Entity
{
class Requirement
{
public:
	Requirement();

	void setHabitId(int id);
	int getHabitId() const;

	void setBeginDate(Dt::Date beginDate);
	Dt::Date getBeginDate() const;

	void setEndDate(Dt::Date beginDate);
	Dt::Date getEndDate() const;

	void setTarget(int target);
	int getTarget() const;

private:
	int habitId;
	Dt::Date beginDate;
	Dt::Date endDate;
	int target;
};

} // namespace Entity

#endif // __REQUIREMENT_H
