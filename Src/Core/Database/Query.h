#ifndef __QUERY_H
#define __QUERY_H

#include <memory>
#include <set>
#include <string>

#include <Core/Database/Database_fwd.h>
#include <Core/Database/Dataset_fwd.h>
#include <Core/Database/Parameters.h>
#include <Core/Database/SQLite_fwd.h>

namespace Db
{

class Query
{
public:
    Query(Database* database, const std::string& sql);
    ~Query();

    std::unique_ptr<Dataset> execute();

    template<typename T>
    void setParam(const std::string& name, T value)
    {
        parameters->setParam(name, value);
    }

private:
    void setDatasetColumns(Dataset* dataset);
    void addDatasetRow(Dataset* dataset);
    void checkForDbError(int dbStatus);

private:
    std::unique_ptr<Parameters> parameters;
    sqlite3_stmt* statement;
    Database* database;
};

} // namespace Db

#endif
