#ifndef __PARAMETERS_H
#define __PARAMETERS_H

#include <set>
#include <string>

#include <Core/Database/Database_fwd.h>
#include <Core/Database/SQLite_fwd.h>

namespace Db
{

class Parameters
{
public:
    Parameters(Db::Database* db, sqlite3_stmt* statement);
    void ensureAllParamsAreSet();

    template<typename T>
    void setParam(const std::string& name, T value);

private:
    void createUnsetParametersList();
    void removeFromUnsetParamsList(const std::string& name);
    int getParamIndex(const std::string& name);
    void checkForDbError(int dbStatus);

private:
    sqlite3_stmt* statement;
    std::set<std::string> unsetParams;
    Db::Database* db;
};

} // namespace Db

#endif // __PARAMETERS_H
