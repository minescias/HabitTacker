#include "Core/Database/Dataset2.h"

#include <Core/Utils/Exceptions/LogicError.h>

namespace Db
{

Dataset2::Dataset2()
{
}

void Dataset2::addColumn(const std::string& name)
{
	if(header.find(name) != header.end())
		throw LogicError("Db: Redefinition of " + name + " column"); 

	header.insert({name, header.size()});
}

Row* Dataset2::addRow()
{
	auto row = data.emplace_back(std::make_unique<Row>(&header)).get();
	return row;
}

int Dataset2::getColumnsCount() const
{
	return (header.size());
}

int Dataset2::getRowsCount() const
{
	return data.size();
}

bool Dataset2::isInitialized() const
{
	return !header.empty();
}

bool Dataset2::isEmpty() const
{
	return data.empty();
}

Row* Dataset2::getFirstRow() const
{
	if (isEmpty())
		throw LogicError("Db: Cannot get first row from empty dataset"); 


	return data.front().get();
}

} // namespace Db
