#include "Core/Database/Row.h"

#include <Core/Strings/Format.h>
#include <Core/Utils/Exceptions/LogicError.h>

namespace Db
{

Row::Row(DatasetHeader* header)
	: header (header)
{
	data.resize(header->size());
}

void Row::set(const std::string& columnName, const std::string& value)
{
	ensureThatColumExists(columnName);
	data[header->at(columnName)] = value;
}

void Row::ensureThatColumExists(const std::string& columnName) const
{
	using Strings::format;

	if (header->find(columnName) == header->end())
		throw LogicError(format("Db: Column '%1%' does not exist", columnName));
}


} // namespace Db
