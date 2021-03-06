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
	return str.append(width - getUtf8StringLength(str), paddigChar);
}

} // namespace

namespace Cli
{
Table::Table()
{
}

void Table::addColumn(const std::string& id, const std::string& alias)
{
	columnIds.push_back(id);
	idToIndexMap.insert(std::make_pair(id, idToIndexMap.size()));

	if (alias.empty())
		columnNames.emplace_back(id);
	else
		columnNames.emplace_back(alias);
}

void Table::addLine()
{
	data.emplace_back(std::vector<std::string>(columnIds.size(), ""));
}

void Table::setValue(const std::string& columnId, const std::string& value)
{
	auto index = getColumnIndex(columnId);
	setValue(index, value);
}

void Table::setValue(int columnIndex, const std::string& value)
{
	data.back()[columnIndex] = value;
}

int Table::getColumnIndex(const std::string& id) const
{
	return idToIndexMap.at(id);
}

void Table::print()
{
	calculateColumnLengts();

	std::cout << "\n";
	printHeader();
	printHeaderSeparator();
	printData();
}

void Table::calculateColumnLengts()
{
	columnWidths.clear();
	for (auto name : columnNames)
		columnWidths.emplace_back(getUtf8StringLength(name));

	for (auto row : data)
	{
		for (unsigned i = 0; i < row.size(); i++)
		{
			auto valueLength = getUtf8StringLength(row[i]);
			if (valueLength > columnWidths[i])
				columnWidths[i] = valueLength;
		}
	}
}

void Table::printHeader() const
{
	auto separator = "";
	for (unsigned i = 0; i < columnIds.size(); i++)
	{
		std::cout << separator << rPad(columnNames[i], columnWidths[i], ' ');
		separator = " ";
	}
	std::cout << "\n";
}

void Table::printHeaderSeparator() const
{
	auto separator = "";
	for (auto width : columnWidths)
	{
		std::cout << separator << std::string(width, '-');
		separator = " ";
	}
	std::cout << "\n";
}

void Table::printData() const
{
	if (data.empty())
		return;

	for (auto line : data)
	{
		auto separator = "";
		for (unsigned i = 0; i < line.size(); i++)
		{
			std::cout << separator << rPad(line[i], columnWidths[i], ' ');
			separator = " ";
		}
		std::cout << "\n";
	}
}

} // namespace Cli
