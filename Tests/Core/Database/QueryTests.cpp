#include <gmock/gmock.h>

#include <memory>
#include <optional>

#include "Core/Database/Database.h"
#include "Core/Database/Dataset.h"
#include "Core/Database/Query.h"
#include "Core/Utils/Exceptions/LogicError.h"

using namespace testing;

// I'm using Query both to prepare data and test :)

class QueryTests : public testing::Test
{
public:
    QueryTests()
        : db(std::make_unique<Db::Database>("Tests.db"))
    {
        dropMainTable();
        createMainTable();
        fillMainTable();
    }

    void dropMainTable()
    {
        auto sql = "drop table if exists main";
        Db::Query(db.get(), sql).execute();
    }

    void createMainTable()
    {
        auto createTableSql =
            "\n create table main("
            "\n     id int primary key not null,"
            "\n     first int,"
            "\n     second char(20),"
            "\n     third double"
            "\n )"
        ;

        Db::Query(db.get(), createTableSql).execute();
    }

    void insertRow(int id, int first, const std::string& second, double third)
    {
        std::stringstream insertSql;

        insertSql <<
            "\n insert into main"
            "\n ("
            "\n     id,"
            "\n     first,"
            "\n     second,"
            "\n     third"
            "\n )"
            "\n values "
            "\n ("
            "\n     " << id << ","
            "\n     " << first << ","
            "\n     '" << second << "',"
            "\n     '" << third << "'"
            "\n )"
        ;

        Db::Query(db.get(), insertSql.str()).execute();
    }

    void fillMainTable()
    {
        insertRow(1, 100, "Sto", 1.1);
        insertRow(2, 1000, "Tysiąc", 1.2);
    }

    void validateThirdRow()
    {
        auto sql = "select * from main m where m.id=3";
        auto result = Db::Query(db.get(), sql).execute();

        validateRow(result.get(), 3, 1000000, "Milijon", 1.3245);
    }

    void validateRow(Db::Dataset* dataset, int id, int first,
        const std::string& second, double third)
    {
        dataset->next();
        ASSERT_THAT(dataset->getAs<int>("id"), Eq(id));
        ASSERT_THAT(dataset->getAs<int>("first"), Eq(first));
        ASSERT_THAT(dataset->getAs<std::string>("second"), Eq(second));
        ASSERT_THAT(dataset->getAs<double>("third"), Eq(third));
    }

    auto getInsertQuery()
    {
        return
            "\n insert into main"
            "\n ("
            "\n     id,"
            "\n     first,"
            "\n     second,"
            "\n     third"
            "\n )"
            "\n values "
            "\n ("
            "\n     :id,"
            "\n     :first,"
            "\n     :second,"
            "\n     :third"
            "\n )"
        ;
    }

    std::unique_ptr<Db::Database> db;
};

// inserting

TEST_F(QueryTests, insertRowWithoutUsingParameters)
{
    auto insertSql =
        "\n insert into main"
        "\n ("
        "\n     id,"
        "\n     first,"
        "\n     second,"
        "\n     third"
        "\n )"
        "\n values "
        "\n ("
        "\n     3,"
        "\n     1000000,"
        "\n     'Milijon',"
        "\n     1.3245"
        "\n )"
    ;

    auto query = Db::Query(db.get(), insertSql);
    query.execute();

    validateThirdRow();
}

TEST_F(QueryTests, insertRowUsingParameters)
{
    auto query = Db::Query(db.get(), getInsertQuery());
    query.setParam(":id", 3);
    query.setParam(":first", 1000000);
    query.setParam(":second", "Milijon");
    query.setParam(":third", 1.3245);
    query.execute();

    validateThirdRow();
}

// select

TEST_F(QueryTests, selectUsingParameters)
{
    auto sql = "select * from main m where m.id = :id";
    auto query = Db::Query(db.get(), sql);
    query.setParam(":id", 2);
    auto result = query.execute();

    validateRow(result.get(), 2, 1000, "Tysiąc", 1.2);
}

TEST_F(QueryTests, selectThatReturnsEmptyDataset)
{
    auto sql = "select * from main m where m.id = :id";
    auto query = Db::Query(db.get(), sql);
    query.setParam(":id", 1000); //some nonexisting index
    auto result = query.execute();

    ASSERT_TRUE(result->initialized());
    ASSERT_TRUE(result->empty());
}

TEST_F(QueryTests, selectMultipleRows)
{
    auto sql = "select * from main m order by m.id";
    auto query = Db::Query(db.get(), sql);
    auto result = query.execute();

    validateRow(result.get(), 1, 100, "Sto", 1.1);
    validateRow(result.get(), 2, 1000, "Tysiąc", 1.2);
}

TEST_F(QueryTests, selectingNullValues)
{
    auto insertSql =
        "\n insert into main"
        "\n ("
        "\n     id,"
        "\n     first"
        "\n )"
        "\n values "
        "\n ("
        "\n     3,"
        "\n     10"
        "\n )";

    Db::Query(db.get(), insertSql).execute();

    auto sql = "select * from main m where m.id = :id";
    auto query = Db::Query(db.get(), sql);
    query.setParam(":id", 3);

    auto dataset = query.execute();

    dataset->next();
    ASSERT_THAT(dataset->getAs<std::string>("second"), Eq(""));
    ASSERT_THAT(dataset->getAs<std::optional<double>>("third"), std::nullopt);
}

// error handling

TEST_F(QueryTests, throwsLogicErrorWhenCannotFindParameter)
{
    try
    {
        auto sql = "select * from main m where m.id = :id";
        auto query = Db::Query(db.get(), sql);
        query.setParam(":nonExistingParam", "");
        FAIL() << "Logic error about non existing parameter shoul be thrown";
    }
    catch(LogicError& err)
    {
        auto expectedMessage = std::string(
            "Could not find parameter :nonExistingParam");

        ASSERT_THAT(err.what(), Eq(expectedMessage));
    }
}

TEST_F(QueryTests, throwsErrorWhenParameterIsNotSet)
{
    try
    {
        auto sql = "select * from main m where m.id = :id";
        auto query = Db::Query(db.get(), sql);
        auto result = query.execute();

        FAIL() << "Logic error about unknown param shoul be thrown";
    }
    catch(const LogicError& err)
    {
        auto expectedMessage = std::string("Query: parameter :id is not set");

        ASSERT_THAT(err.what(), Eq(expectedMessage));
    }
}
