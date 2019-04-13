#include <gmock/gmock.h>

#include "Core/Database/Dataset.h"
#include "Core/Utils/Exceptions/LogicError.h"

using namespace testing;

class DatasetTests : public testing::Test
{

public:
    void initDataset()
    {
        dataset.addColumn("First");
        dataset.addColumn("Second");

        firstRow = {"1", "One"};
        secondRow = {"2", "Two"};

        dataset.addRow(firstRow);
        dataset.addRow(secondRow);
    }

    void validateCurrentRow(Db::Dataset::Row row)
    {
        ASSERT_THAT(dataset.getAs<std::string>("First"), row[0]);
        ASSERT_THAT(dataset.getAs<std::string>("Second"), row[1]);
    }

    Db::Dataset dataset;
    Db::Dataset::Row firstRow;
    Db::Dataset::Row secondRow;
};

// inserting values
TEST_F(DatasetTests, addsColumnAndRetunrsColumnsCount)
{
    Db::Dataset dataset;
    EXPECT_THAT(dataset.getColumnsCount(), Eq(0));

    dataset.addColumn("First");
    EXPECT_THAT(dataset.getColumnsCount(), Eq(1));

    dataset.addColumn("Second");
    EXPECT_THAT(dataset.getColumnsCount(), Eq(2));
}

TEST_F(DatasetTests, addRowsAndReturnsRowsCount)
{
    Db::Dataset dataset;
    dataset.addColumn("First");
    dataset.addColumn("Second");

    EXPECT_THAT(dataset.getRowsCount(), Eq(0));

    dataset.addRow({"1", "One"});
    EXPECT_THAT(dataset.getRowsCount(), Eq(1));

    dataset.addRow({"2", "Two"});
    EXPECT_THAT(dataset.getRowsCount(), Eq(2));
}

// iterating/accessing data
TEST_F(DatasetTests, returnsFirstRowAfterSet)
{
    initDataset();
    validateCurrentRow(firstRow);
}

TEST_F(DatasetTests, ignoresFirsNextCommand)
{
    // dataset should be used with while loop so the first next() command
    // has to be ignored ( e.g. while(dataset.next()){...} )
    initDataset();
    validateCurrentRow(firstRow);
    dataset.next();
    validateCurrentRow(firstRow);
}

TEST_F(DatasetTests, nextMovesToNextRow)
{
    initDataset();
    dataset.next(); // ignored - see previous test
    dataset.next();
    validateCurrentRow(secondRow);
}

TEST_F(DatasetTests, nextRerunsTrueWhenNextRowAvailable)
{
    initDataset();
    ASSERT_TRUE(dataset.next());
}

TEST_F(DatasetTests, nextReturnsFalseWhenNoMoreRowsAvailable)
{
    initDataset();
    dataset.next();
    dataset.next();

    ASSERT_FALSE(dataset.next());
}

TEST_F(DatasetTests, nextAllowsToIterateEntireDatasetUsingWhile)
{
    initDataset();
    auto expectedIterations = dataset.getRowsCount();
    auto actualIterations = 0;

    while (dataset.next())
        actualIterations++;

    ASSERT_THAT(actualIterations, Eq(expectedIterations));
}

TEST_F(DatasetTests, isInitializedTest)
{
    EXPECT_FALSE(dataset.initialized());
    dataset.addColumn("First");
    dataset.addColumn("Second");
    EXPECT_TRUE(dataset.initialized());
}

TEST_F(DatasetTests, isEmptyTest)
{
    dataset.addColumn("First");
    dataset.addColumn("Second");
    EXPECT_TRUE(dataset.empty());
    dataset.addRow(firstRow);
    EXPECT_FALSE(dataset.empty());
}

// getting values from dataset

TEST_F(DatasetTests, gettingColumnByNameIsNotCaseSensitive)
{
    initDataset();
    dataset.next();

    ASSERT_THAT(dataset.getAs<int>("First"), Eq(dataset.getAs<int>("FiRsT")));
}

TEST_F(DatasetTests, castValueToSpecificType)
{
    initDataset();
    EXPECT_THAT(dataset.getAs<int>("First"), Eq(1));
    EXPECT_THAT(dataset.getAs<double>("First"), Eq(1.0));
    EXPECT_THAT(dataset.getAs<std::string>("Second"), Eq("One"));
}

TEST_F(DatasetTests, castToOptionalIntValues)
{
    dataset.addColumn("First");
    dataset.addColumn("Second");
    dataset.addRow(Db::Dataset::Row{"1", ""});

    EXPECT_THAT(dataset.getAs<std::optional<int>>("First"), std::make_optional<int>(1));
    EXPECT_THAT(dataset.getAs<std::optional<int>>("Second"), std::nullopt);
}

TEST_F(DatasetTests, castToOptionalDoubleValues)
{
    dataset.addColumn("First");
    dataset.addColumn("Second");
    dataset.addRow(Db::Dataset::Row{"1.32", ""});

    EXPECT_THAT(dataset.getAs<std::optional<double>>("First"), std::make_optional<double>(1.32));
    EXPECT_THAT(dataset.getAs<std::optional<double>>("Second"), std::nullopt);
}

// error handling0

TEST_F(DatasetTests, throwsErrorWhenTryingToCastEmtyValueToNonNullableOnject)
{
    dataset.addColumn("First");
    dataset.addColumn("Second");
    dataset.addRow(Db::Dataset::Row{"", ""});

    try
    {
        dataset.getAs<int>("First");
        FAIL() << "Expected logic error about casting to non nullable object";
    }
    catch(LogicError& err)
    {
        auto expected = "Cannot cast empty value of column \"First"
            "\" to non nullable object";

        ASSERT_STREQ(err.what(), expected);
    }
}

TEST_F(DatasetTests, throwsLogicErrorWhenCannotCastToInt)
{
    try
    {
        initDataset();
        dataset.getAs<int>("Second");
        FAIL() << "Should throw logic error";
    }
    catch(LogicError& err)
    {
        auto expected =
            "Dataset: Can't cast column 'Second' value 'One' to int";

        ASSERT_STREQ(err.what(), expected);
    }
}

TEST_F(DatasetTests, throwsLogicErrorWhenCannotCastToDouble)
{
    try
    {
        initDataset();
        dataset.getAs<double>("Second");
        FAIL() << "Should throw logic error";
    }
    catch(LogicError& err)
    {
        std::string expectedMessage
            = "Dataset: Can't cast column 'Second' value 'One' to double";

        ASSERT_THAT(err.what(), Eq(expectedMessage));
    }
}

TEST_F(DatasetTests, throwsLogicErrorWhenSelectingNonexistingColumn)
{
    try
    {
        initDataset();
        dataset.getAs<double>("NonexistingColumn");
        FAIL() << "Should throw logic error";
    }
    catch(LogicError& err)
    {
        std::string expectedMessage = "Dataset: "
            "Trying to access nonexisting column (NonexistingColumn)";

        ASSERT_THAT(err.what(), Eq(expectedMessage));
    }
}
