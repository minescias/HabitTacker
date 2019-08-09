#include "Core/Database/Dataset.h"

#include <Core/Exceptions/LogicError.h>

namespace Db
{

Dataset::Dataset()
{
}

void Dataset::addColumn(const std::string& name)
{
	if(header.find(name) != header.end())
		throw LogicError("Db: Redefinition of " + name + " column"); 

	header.insert({name, header.size()});
}

Row* Dataset::addRow()
{
	auto row = data.emplace_back(std::make_unique<Row>(&header)).get();
	return row;
}

int Dataset::getColumnsCount() const
{
	return (header.size());
}

int Dataset::getRowsCount() const
{
	return data.size();
}

bool Dataset::initialized() const
{
	return !header.empty();
}

bool Dataset::empty() const
{
	return data.empty();
}

Row* Dataset::getFirstRow() const
{
	if (empty())
		throw LogicError("Db: Cannot get first row from empty dataset"); 


	return data.front().get();
}

} // namespace Db
