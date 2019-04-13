#ifndef __DATABASE_H
#define __DATABASE_H

#include <string>

#include "Core/Database/Database_fwd.h"

struct sqlite3;

namespace Db
{

class Database
{
public:
    Database(const std::string& name);
    ~Database();

    sqlite3* getHandler();

private:
    void connect(const std::string& name);
    void disconnect();

    std::string databaseName;
    sqlite3* handler;
};

} // namespace Db

#endif
