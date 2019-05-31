#ifndef __DATE_LITERAL_H
#define __DATE_LITERAL_H

#include <string>

#include <Core/DateTime/Timestamp.h>

namespace Dt
{

class DateLiteral
{
public:
	DateLiteral();
	Timestamp parse(const std::string& date);
};

} // namespace Dt

#endif // __DATE_LITERAL_H
