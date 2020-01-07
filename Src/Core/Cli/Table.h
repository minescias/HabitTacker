#ifndef __TABLE_H
#define __TABLE_H

#include <string>
#include <vector>
#include <map>

namespace Cli
{
class Table
{
public:
	Table();
	void addColumn(const std::string& name);
	void print() const;
	void setValue(const std::string& columnName, const std::string& value);
	void addLine();

private:
	std::vector<std::string> columnNames;
	std::map<std::string, int> nameToIndexMap;
	std::vector<std::vector<std::string>> data;
};

} // namespace Cli

#endif // __TABLE_H
