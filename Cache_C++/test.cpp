#include "pch.h"
//#include "../../Cache_C++/Cache_C++/arc.h"
#include "arc.h"

TEST(Min_Max, Min) {
	size_t res = min(1, 2);
	EXPECT_EQ(res, 1);
}

TEST(Min_Max, Max) {
	size_t res = max(1, 2);
	EXPECT_EQ(res, 2);
}

TEST(Lookups, Size2_Elem10) {
	const size_t count = 10;
	cache_t<int> ARC{ 2 };
	int arr[count] = { 9, 8, 8, 7, 8, 2, 7, 3, 4, 6 };
	int res = ARC.lookups(count, arr);
	EXPECT_EQ(res, 2);
}

TEST(Lookups, Size3_Elem10_1) {
	const size_t count = 10;
	cache_t<int> ARC{ 3 };
	int arr[count] = { 1, 7, 9, 9, 4, 7, 7, 9, 5, 9 };
	int res = ARC.lookups(count, arr);
	EXPECT_EQ(res, 5);
}

TEST(Lookups, Size1_Elem5) {
	const size_t count = 5;
	cache_t<int> ARC{ 1 };
	int arr[count] = { 4, 2, 3, 1, 4 };
	int res = ARC.lookups(count, arr);
	EXPECT_EQ(res, 0);
}

TEST(Lookups, Size1_Elem6) {
	const size_t count = 6;
	cache_t<int> ARC{ 1 };
	int arr[count] = { 1, 0, 0, 0, 0, 0 };
	int res = ARC.lookups(count, arr);
	ARC.clear();
	EXPECT_EQ(res, 4);
}

TEST(Lookups, Size3_Elem10_2) {
	const size_t count = 10;
	cache_t<int> ARC{ 3 };
	int arr[count] = { 4, 6, 6, 2, 6, 5, 7, 6, 5, 1 };
	int res = ARC.lookups(count, arr);
	ARC.clear();
	EXPECT_EQ(res, 4);
}

TEST(Lookups, Size4_Elem10_1) {
	const size_t count = 10;
	cache_t<int> ARC{ 4 };
	int arr[count] = { 8, 8, 8, 5, 4, 1, 9, 1, 3, 2 };
	int res = ARC.lookups(count, arr);
	ARC.clear();
	EXPECT_EQ(res, 3);
}

TEST(Lookups, Size4_Elem10_2) {
	const size_t count = 10;
	cache_t<int> ARC{ 4 };
	int arr[count] = { 5, 9, 7, 0, 5, 5, 3, 7, 4, 4 };
	int res = ARC.lookups(count, arr);
	ARC.clear();
	EXPECT_EQ(res, 4);
}

TEST(Lookups, Size3_Elem7) {
	const size_t count = 7;
	cache_t<int> ARC{ 3 };
	int arr[count] = { 3, 2, 4, 6, 9, 7, 5 };
	int res = ARC.lookups(count, arr);
	ARC.clear();
	EXPECT_EQ(res, 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}