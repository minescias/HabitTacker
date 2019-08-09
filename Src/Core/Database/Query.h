#ifndef __QUERY_H
#define __QUERY_H

#include <memory>
#include <set>
#include <string>

#include <Core/Database/Database_fwd.h>
#include <Core/Database/Dataset2.h>
#include <Core/Database/Parameters.h>
#include <Core/Database/SQLite_fwd.h>

namespace Db
{

class Query
{
public:
    Query(Database* database, const std::string& sql);
    ~Query();

    void executeCommand();
    Dataset2 execute2();

    template<typename T>
    void setParam(const std::string& name, T value)
    {
        parameters->setParam(name, value);
    }

private:
    int runQuery();
    void checkForDbError(int dbStatus);

private:
    std::unique_ptr<Parameters> parameters;
    sqlite3_stmt* statement;
    Database* database;
};

} // namespace Db

#endif
