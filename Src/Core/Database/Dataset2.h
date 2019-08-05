#ifndef __DATASET2_H
#define __DATASET2_H

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <Core/Database/DatasetHeader.h>
#include <Core/Database/Row.h>

namespace Db
{

class Dataset2
{
public:
	Dataset2();

	void addColumn(const std::string& name);
	Row* addRow();

	int getColumnsCount() const;
	int getRowsCount() const;

	bool isInitialized() const;
	bool isEmpty() const;

	Row* getFirstRow() const;

private:
	DatasetHeader header;
	std::vector<std::unique_ptr<Row>> data;
};

} // namespace Db

#endif // __DATASET2_H
