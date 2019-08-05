#include <gmock/gmock.h>

#include <Core/Database/Dataset2.h>

namespace Tests
{

using namespace testing;

class Dataset2Tests : public testing::Test
{
public:
	Dataset2Tests(){};

	void initDataset()
	{
		dataset.addColumn("foo");
		dataset.addColumn("bar");
	}

	Db::Dataset2 dataset;
};

TEST_F(Dataset2Tests, gets_columns_count)
{
	initDataset();
	ASSERT_THAT(dataset.getColumnsCount(), Eq(2));
}

TEST_F(Dataset2Tests, gets_rows_count)
{
	initDataset();

	dataset.addRow();
	dataset.addRow();

	ASSERT_THAT(dataset.getRowsCount(), Eq(2));
}

TEST_F(Dataset2Tests, returns_first_row)
{
	initDataset();

	auto r1 = dataset.addRow();
	r1->set("foo", "123");
	r1->set("bar", "456");

	auto r2 = dataset.addRow();
	r2->set("foo", "000");
	r2->set("bar", "999");


	auto firstRow = dataset.getFirstRow();
	EXPECT_THAT(firstRow->get<std::string>("foo"), Eq("123"));
	EXPECT_THAT(firstRow->get<std::string>("bar"), Eq("456"));
}

TEST_F(Dataset2Tests, returns_true_if_initialized)
{
	EXPECT_FALSE(dataset.isInitialized());
	initDataset();
	EXPECT_TRUE(dataset.isInitialized());
}

TEST_F(Dataset2Tests, returns_true_if_empty)
{
	initDataset();
	EXPECT_TRUE(dataset.isEmpty());
	dataset.addRow();
	EXPECT_FALSE(dataset.isEmpty());
}

// todo
// for range loops

// error handling:
// * column redefinition
// * when there is no data and trying to get first row

} // namespace Tests