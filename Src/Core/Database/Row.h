#ifndef __ROW_H
#define __ROW_H

#include <map>
#include <string>
#include <vector>

#include <Core/Database/ValueGetter.h>

namespace Db
{

// column name to index
using DatasetHeader = std::map<std::string, int>; 

class Row
{
public:
	Row(DatasetHeader* header);

	void set(const std::string& columnName, const std::string& value);

	template<typename T>
	T get(const std::string& columnName) const
	{
		ensureThatColumExists(columnName);
		return Db::getVal<T>(columnName, data[header->at(columnName)]);
	}

private:
	void ensureThatColumExists(const std::string& columnName) const;

private:
	DatasetHeader* header;
	std::vector<std::string> data;
};

} // namespace Db

#endif // __ROW_H
