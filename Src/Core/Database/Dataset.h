#ifndef __DATASET_H
#define __DATASET_H

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "Core/Database/Dataset_fwd.h"

namespace Db
{

class Dataset
{
public:
    typedef std::vector<std::string> Row;

    Dataset();

    void addColumn(const std::string& name);
    void addRow(const Row& row);
    bool next();
    bool initialized() const;
    bool empty() const;
    int getColumnsCount();
    int getRowsCount();

    template <class T>
    T getAs(const std::string& name);

private:
    std::string getColumnValue(const std::string& name) const;
    void assertInitialized() const;
    void assertValueIsNotEmpty(const std::string& name) const;

private:
    std::map<std::string, int> columns;
    std::vector<Row> data;
    std::vector<Row>::iterator currentRow;

    bool firstNextIgnored;
};

} // namespace Db

#endif
