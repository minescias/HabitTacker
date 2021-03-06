#include <gmock/gmock.h>

#include <Core/Database/Dataset.h>
#include <Core/Exceptions/LogicError.h>

namespace Tests
{

using namespace testing;

class DatasetTests : public testing::Test
{
public:
	DatasetTests(){};

	void initDataset()
	{
		dataset.addColumn("foo");
		dataset.addColumn("bar");
	}

	void addRows()
	{
		auto r1 = dataset.addRow();
		r1->set("foo", "123");
		r1->set("bar", "456");

		auto r2 = dataset.addRow();
		r2->set("foo", "000");
		r2->set("bar", "999");
	}
	
	Db::Dataset createConstDataset()
	{
		Db::Dataset dataset;

		dataset.addColumn("foo");
		dataset.addColumn("bar");

		auto r1 = dataset.addRow();
		r1->set("foo", "123");
		r1->set("bar", "456");

		auto r2 = dataset.addRow();
		r2->set("foo", "000");
		r2->set("bar", "999");

		return dataset;
	}

	Db::Dataset dataset;
};

TEST_F(DatasetTests, gets_columns_count)
{
	initDataset();
	ASSERT_THAT(dataset.getColumnsCount(), Eq(2));
}

TEST_F(DatasetTests, gets_rows_count)
{
	initDataset();
	addRows();

	ASSERT_THAT(dataset.getRowsCount(), Eq(2));
}

TEST_F(DatasetTests, returns_first_row)
{
	initDataset();
	addRows();

	auto firstRow = dataset.getFirstRow();
	EXPECT_THAT(firstRow->get<std::string>("foo"), Eq("123"));
	EXPECT_THAT(firstRow->get<std::string>("bar"), Eq("456"));
}

TEST_F(DatasetTests, returns_true_if_initialized)
{
	EXPECT_FALSE(dataset.initialized());
	initDataset();
	EXPECT_TRUE(dataset.initialized());
}

TEST_F(DatasetTests, returns_true_if_empty)
{
	initDataset();
	EXPECT_TRUE(dataset.empty());
	dataset.addRow();
	EXPECT_FALSE(dataset.empty());
}

TEST_F(DatasetTests, allows_to_iterate_using_range_for_loop)
{
	initDataset();
	addRows();
	
	auto index{0};

	for(auto& row: dataset)
	{
		if (index == 0)
		{
			EXPECT_THAT(row.get<std::string>("foo"), Eq("123"));
			EXPECT_THAT(row.get<std::string>("bar"), Eq("456"));
			index++;
		}
		else
		{
			EXPECT_THAT(row.get<std::string>("foo"), Eq("000"));
			EXPECT_THAT(row.get<std::string>("bar"), Eq("999"));
		}
	}
}

TEST_F(DatasetTests, allows_to_iterate_using_range_for_loop_on_const_object)
{

	const auto dataset = createConstDataset();
	auto index{0};
	
	for(const auto& row: dataset)
	{
		if (index == 0)
		{
			EXPECT_THAT(row.get<std::string>("foo"), Eq("123"));
			EXPECT_THAT(row.get<std::string>("bar"), Eq("456"));
			index++;
		}
		else
		{
			EXPECT_THAT(row.get<std::string>("foo"), Eq("000"));
			EXPECT_THAT(row.get<std::string>("bar"), Eq("999"));
		}
	}	
}

TEST_F(DatasetTests, trows_logic_error_on_colum_redefinition)
{
	Db::Dataset dataset;
	dataset.addColumn("foo");

	try
	{
		dataset.addColumn("foo");
		FAIL();
	}
	catch(LogicError& err)
	{
		auto expected = "Db: Redefinition of foo column";
		ASSERT_STREQ(err.what(), expected);
	}
}

TEST_F(DatasetTests, throw_logic_error_when_threre_is_no_data_and_trying_to_get_first_row)
{
	initDataset();

	try
	{
		dataset.getFirstRow();
		FAIL();
	}
	catch(LogicError& err)
	{
		auto expected = "Db: Cannot get first row from empty dataset";
		ASSERT_STREQ(err.what(), expected);
	}
}
// * when there is no data and trying to get first row

} // namespace Tests