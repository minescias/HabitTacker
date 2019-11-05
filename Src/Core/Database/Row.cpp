#include "Core/Database/Row.h"

#include <fmt/format.h>

#include <Core/Exceptions/LogicError.h>

namespace Db
{
Row::Row(DatasetHeader* header) : header(header)
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
	if (header->find(columnName) == header->end())
		throw LogicError(fmt::format("Db: Column '{}' does not exist", columnName));
}

} // namespace Db
