#ifndef __DATE_LITERAL_H
#define __DATE_LITERAL_H

#include <string>

#include <Core/DateTime/Date.h>

namespace Dt
{
class DateLiteral
{
public:
	DateLiteral() = default;
	Date parse(const std::string& date);
};

} // namespace Dt

#endif // __DATE_LITERAL_H
