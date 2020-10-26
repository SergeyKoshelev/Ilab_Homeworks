#include "pch.h"
//#include "Tree.h"
//#include "Triangles.h"
#include "../../Triangles/Tree.h"
#include "../../Triangles/Triangles.h"


TEST(_2trian, just_int) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 2; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{-1, -1, 0}, Triangle::Point{ 1, 0, 0 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{0, 0, -1}, Triangle::Point{ -1, 1, 1 }, Triangle::Point{ 1, -1, 1 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], true);
	tree.free();
	arr.clear();
}

TEST(_3trian, just_int) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 3; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{0, 0, 0}, Triangle::Point{ 1, 0, 0 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{5, 5, 5}, Triangle::Point{ 5, 5, 5 }, Triangle::Point{ 5, 5, 5 } });
	tree.tr_push(Triangle{ 2, Triangle::Point{0, 0.5, -0.5}, Triangle::Point{ 0, 0.5, 0.5 }, Triangle::Point{ -1, 0, 0 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], false);
	EXPECT_EQ(arr[2], true);
	tree.free();
	arr.clear();
}

TEST(_2trian, parallel) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 2; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{0, 1, 0}, Triangle::Point{ 0, 0, 0 }, Triangle::Point{ 1, 0, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{0, 1, -1}, Triangle::Point{ 0, 0, -1 }, Triangle::Point{ 1, 0, -1 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], false);
	EXPECT_EQ(arr[1], false);
	tree.free();
	arr.clear();
}

TEST(_3trian, have_line_but_no) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 3; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{-1, 1, 0}, Triangle::Point{ 1, -1, 0 }, Triangle::Point{ 1, 3, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{-1, 7, 0}, Triangle::Point{ 1, 5, 0 }, Triangle::Point{ 1, 9, 0 } });
	tree.tr_push(Triangle{ 2, Triangle::Point{0, 4, -1}, Triangle::Point{ 0, 2, 1 }, Triangle::Point{ 0, 6, 1 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], false);
	EXPECT_EQ(arr[1], false);
	EXPECT_EQ(arr[2], false);
	tree.free();
	arr.clear();
}

TEST(_3trian, have_line_and_yes) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 3; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{-1, 3, 0}, Triangle::Point{ 1, 0, 0 }, Triangle::Point{ 1, 3, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{-1, 5, 0}, Triangle::Point{ 1, 5, 0 }, Triangle::Point{ 1, 8, 0 } });
	tree.tr_push(Triangle{ 2, Triangle::Point{0, 4, -1}, Triangle::Point{ 0, 2, 1 }, Triangle::Point{ 0, 6, 1 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], true);
	EXPECT_EQ(arr[2], true);
	tree.free();
	arr.clear();
}

TEST(int_2D, line_segs_and_inside) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 2; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{0, -2, 0}, Triangle::Point{ 0, 2, 0 }, Triangle::Point{ 2, 0, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{1, -2, 0}, Triangle::Point{ 1, 2, 0 }, Triangle::Point{ 3, 0, 0 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], true);
	tree.free();
	arr.clear();
}

TEST(int_2D, inside) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 2; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{-2, 4, 0}, Triangle::Point{ -2, -4, 0 }, Triangle::Point{ 4, 0, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{-1, 2, 0}, Triangle::Point{ -1, -2, 0 }, Triangle::Point{ 2, 0, 0 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], true);
	tree.free();
	arr.clear();
}

TEST(int_2D, only_line_segs) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 2; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{-2, 4, 0}, Triangle::Point{ -2, -4, 0 }, Triangle::Point{ 4, 0, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{2, 4, 0}, Triangle::Point{ 2, -4, 0 }, Triangle::Point{ -4, 0, 0 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], true);
	tree.free();
	arr.clear();
}

TEST(many_similar, count6) {
	using namespace Triangles;
	std::vector<bool> arr;
	for (int i = 0; i < 6; i++) { arr.push_back(false); }
	Tree::Ternary_Tree tree;

	tree.tr_push(Triangle{ 0, Triangle::Point{1, 0, 0}, Triangle::Point{ 0, 0, 1 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 1, Triangle::Point{1, 0, 0}, Triangle::Point{ 0, 0, 1 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 2, Triangle::Point{1, 0, 0}, Triangle::Point{ 0, 0, 1 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 3, Triangle::Point{1, 0, 0}, Triangle::Point{ 0, 0, 1 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 4, Triangle::Point{1, 0, 0}, Triangle::Point{ 0, 0, 1 }, Triangle::Point{ 0, 1, 0 } });
	tree.tr_push(Triangle{ 5, Triangle::Point{1, 0, 0}, Triangle::Point{ 0, 0, 1 }, Triangle::Point{ 0, 1, 0 } });
	tree.undergo(arr);

	EXPECT_EQ(arr[0], true);
	EXPECT_EQ(arr[1], true);
	EXPECT_EQ(arr[2], true);
	EXPECT_EQ(arr[3], true);
	EXPECT_EQ(arr[4], true);
	EXPECT_EQ(arr[5], true);
	tree.free();
	arr.clear();
}

