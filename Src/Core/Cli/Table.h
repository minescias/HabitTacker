#ifndef __TABLE_H
#define __TABLE_H

#include <map>
#include <string>
#include <vector>

namespace Cli
{
class Table
{
public:
	Table();
	void addColumn(const std::string& name);
	void addLine();
	void setValue(const std::string& columnName, const std::string& value);
	void print();

private:
	void calculateColumnLengts();
	void printHeader() const;
	void printHeaderSeparator() const;
	void printData() const;

private:
	std::vector<int> columnWidths;
	std::vector<std::string> columnNames;
	std::map<std::string, int> nameToIndexMap;
	std::vector<std::vector<std::string>> data;
};

} // namespace Cli

#endif // __TABLE_H
