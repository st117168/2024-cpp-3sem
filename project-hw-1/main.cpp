#include <gtest/gtest.h>
#include "dataset.h"

TEST(TestGroupName_txt, Subtest_1_ColumnCount) 
{
	Dataset data_txt("./data-files/data.txt", 1);
	ASSERT_EQ(data_txt.GetColumnCount(), 3);
}

TEST(TestGroupName_txt, Subtest_2_RowCount) 
{
	Dataset data_txt("./data-files/data.txt", 1);
	ASSERT_EQ(data_txt.GetRowCount(0), 3);
	ASSERT_EQ(data_txt.GetRowCount(1), 3);
	ASSERT_EQ(data_txt.GetRowCount(2), 3);
}

TEST(TestGroupName_txt, Subtest_3_ColumnTypes) 
{
	Dataset data_txt("./data-files/data.txt", 1);
	ASSERT_EQ(data_txt.GetColumnType(0), TypeData::kInt);
	ASSERT_EQ(data_txt.GetColumnType(1), TypeData::kString);
	ASSERT_EQ(data_txt.GetColumnType(2), TypeData::kDouble);
}

TEST(TestGroupName_txt, Subtest_4_ColumnNames) 
{
	Dataset data_txt("./data-files/data.txt", 1);
	ASSERT_EQ(data_txt.GetColumnName(0), "col1");
	ASSERT_EQ(data_txt.GetColumnName(1), "col2");
	ASSERT_EQ(data_txt.GetColumnName(2), "col3");
}

TEST(TestGroupName_txt, Subtest_5_FileWithoutIndexColumn) 
{
	Dataset data2_txt("./data-files/data2.txt", 0);
	ASSERT_EQ(data2_txt.GetColumnCount(), 3);
	ASSERT_EQ(data2_txt.GetRowCount(0), 3);
	ASSERT_EQ(data2_txt.GetColumnType(0), TypeData::kInt);
	ASSERT_EQ(data2_txt.GetColumnName(2), "col3");
}

TEST(TestGroupName_txt, Subtest_6_FileWithoutColumnNames) 
{
	Dataset data3_txt("./data-files/data3.txt", 0, DataLine("col1 col2 col3 col4 col5 col6 col7 col8", ' ', 8));
	ASSERT_EQ(data3_txt.GetColumnCount(), 8);
	ASSERT_EQ(data3_txt.GetRowCount(0), 6);
	ASSERT_EQ(data3_txt.GetColumnType(1), TypeData::kString);
	ASSERT_EQ(data3_txt.GetColumnName(6), "col7");
}

TEST(TestGroupName_csv, Subtest_1_ColumnCount) 
{
	Dataset data_csv("./data-files/data.csv", 1);
	ASSERT_EQ(data_csv.GetColumnCount(), 3);
}

TEST(TestGroupName_csv, Subtest_2_RowCount) 
{
	Dataset data_csv("./data-files/data.csv", 1);
	ASSERT_EQ(data_csv.GetRowCount(0), 3);
	ASSERT_EQ(data_csv.GetRowCount(1), 3);
	ASSERT_EQ(data_csv.GetRowCount(2), 3);
}

TEST(TestGroupName_csv, Subtest_3_ColumnTypes) 
{
	Dataset data_csv("./data-files/data.csv", 1);
	ASSERT_EQ(data_csv.GetColumnType(0), TypeData::kInt);
	ASSERT_EQ(data_csv.GetColumnType(1), TypeData::kString);
	ASSERT_EQ(data_csv.GetColumnType(2), TypeData::kDouble);
}

TEST(TestGroupName_csv, Subtest_4_ColumnNames) 
{
	Dataset data_csv("./data-files/data.csv", 1);
	ASSERT_EQ(data_csv.GetColumnName(0), "col1");
	ASSERT_EQ(data_csv.GetColumnName(1), "col2");
	ASSERT_EQ(data_csv.GetColumnName(2), "col3");
}

TEST(TestGroupName_csv, Subtest_5_FileWithoutIndexColumn) 
{
	Dataset data2_csv("./data-files/data2.csv", 0);
	ASSERT_EQ(data2_csv.GetColumnCount(), 3);
	ASSERT_EQ(data2_csv.GetRowCount(0), 3);
	ASSERT_EQ(data2_csv.GetColumnType(0), TypeData::kInt);
	ASSERT_EQ(data2_csv.GetColumnName(2), "col3");
}

TEST(TestGroupName_csv, Subtest_6_FileWithoutColumnNames) 
{
	Dataset data3_csv("./data-files/data3.csv", 0, DataLine("col1 col2 col3 col4 col5 col6 col7 col8", ' ', 8));
	ASSERT_EQ(data3_csv.GetColumnCount(), 8);
	ASSERT_EQ(data3_csv.GetRowCount(0), 6);
	ASSERT_EQ(data3_csv.GetColumnType(1), TypeData::kString);
	ASSERT_EQ(data3_csv.GetColumnName(6), "col7");
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
