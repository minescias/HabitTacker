#ifndef __DURATION_H
#define __DURATION_H

#include "Core/DateTime/Timestamp.h"

namespace Dt
{

class Duration
{
public:
	Duration(Dt::Timestamp timestamp);

	int getDays() const;

private:
	Dt::Timestamp timestamp;
};

} // namespace Dt

#endif // __DURATION_H
