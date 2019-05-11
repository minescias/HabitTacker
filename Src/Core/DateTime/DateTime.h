#ifndef __DATE_TIME_H
#define __DATE_TIME_H

#include <string>

#include "Core/DateTime/Timestamp.h"

namespace Dt
{

class DateTime
{
public:
	DateTime(const std::string& dateString);
	DateTime(Timestamp date);

	Timestamp unixTime() const;
	std::string dateString() const;

private:
	bool validateDateStringFormat(const std::string& dateString) const;
	bool validateDateValues(const std::tm& tm) const;
	std::string getErrorMessage(const std::string& dateString) const;

private:
	Timestamp timestamp;
};

} // namespace Dt

#endif // __DATE_TIME_H
