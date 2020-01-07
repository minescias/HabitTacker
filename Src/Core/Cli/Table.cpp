#include "Core/Cli/Table.h"

#include <iomanip>
#include <iostream>

namespace
{
// https://stackoverflow.com/questions/4063146/getting-the-actual-length-of-a-utf-8-encoded-stdstring
int getUtf8StringLength(const std::string& str)
{
	int len = 0;

	for (auto c : str)
		len += (c & 0xc0) != 0x80;

	return len;
}

std::string rPad(std::string str, int width, char paddigChar)
{
	return str.append(width - str.length(), paddigChar);
}

} // namespace

namespace Cli
{
Table::Table()
{
}

void Table::addColumn(const std::string& name)
{
	columnNames.push_back(name);
	nameToIndexMap.insert(std::make_pair(name, nameToIndexMap.size()));
}

void Table::print() const
{
	auto headerStr = std::string();

	auto columnsWidth = std::vector<int>();

	std::cout << "\n";
	auto separator = "";
	for (auto name : columnNames)
	{
		std::cout << separator + name;
		columnsWidth.emplace_back(getUtf8StringLength(name));
		separator = " ";
	}
	std::cout << "\n";

	separator = "";
	for (auto width : columnsWidth)
	{
		std::cout << separator << std::string(width, '-');
		separator = " ";
	}
	separator = "";
	std::cout << "\n";

	if (data.empty())
		return;

	for (auto line : data)
	{
		separator = "";
		for (unsigned i = 0; i < line.size(); i++)
		{
			std::cout << separator << rPad(line[i], columnsWidth[i], ' ');
			separator = " ";
		}
		std::cout << "\n";
	}
}

void Table::setValue(const std::string& columnName, const std::string& value)
{
	auto index = nameToIndexMap.at(columnName);
	data.back()[index] = value;
}

void Table::addLine()
{
	data.emplace_back(std::vector<std::string>(columnNames.size(), ""));
}

} // namespace Cli
