#include "pch.h"
//#include "../../Triangles/Triangles/Triangles.h"
#include "Triangles.h"

TEST(DoubleMinMax, Min) {
	double res = min(3.2455789, 3.2455788);
  EXPECT_EQ(res, 3.2455788);
}

TEST(DoubleMinMax, Max) {
	double res = max(11.827348, 11.827349);
	EXPECT_EQ(res, 11.827349);
}

TEST(PointInTriangle, Inside) {
	Point point = { 5, 6 };
	Triangle triangle = { {2, 1}, {4, 8}, {9,3} };
	triangle.init_segs();
	bool res = triangle.contains_point(point);
	EXPECT_EQ(res, true);
}

TEST(PointInTriangle, On_Side) {
	Point point = { -5, 2 };
	Triangle triangle = { {-3, 8}, {3, -6}, {-8, -7} };
	triangle.init_segs();
	bool res = triangle.contains_point(point);
	EXPECT_EQ(res, true);
}

TEST(PointInTriangle, Outside) {
	Point point = { 0, 0 };
	Triangle triangle = { {1, -0.5}, {2, 3}, {-1, 1} };
	triangle.init_segs();
	bool res = triangle.contains_point(point);
	EXPECT_EQ(res, false);
}

TEST(Int_LineSegs, Int_in_middle) {
	Line_seg ls1 = { {1, 2}, {4, 7} };
	Line_seg ls2 = { {-1, 6}, {4, 3} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, true);
}

TEST(Int_LineSegs, Int_End_on_middle) {
	Line_seg ls1 = { {-3, 4}, {0, 1} };
	Line_seg ls2 = { {2, 5}, {-2, -3} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, true);
}

TEST(Int_LineSegs, Int_End_in_end) {
	Line_seg ls1 = { {0, -1}, {-2, 3} };
	Line_seg ls2 = { {0, -1}, {5, 2} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, true);
}

TEST(Int_LineSegs, Int_On1Line_belongs) {
	Line_seg ls1 = { {0, 1}, {5, 2} };
	Line_seg ls2 = { {-1, 0.8}, {6, 2.2} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, true);
}

TEST(Int_LineSegs, Int_On1Line_not_end_not_belongs) {
	Line_seg ls1 = { {0, 1}, {6, 2.2} };
	Line_seg ls2 = { {-1, 0.8}, {5, 2} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, true);
}

TEST(Int_LineSegs, Int_On1Line_end_in_end) {
	Line_seg ls1 = { {-2, -3}, {0, 0} };
	Line_seg ls2 = { {0, 0}, {4, 6} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, true);
}

TEST(Int_LineSegs, NotInt_faraway) {
	Line_seg ls1 = { {0, 5}, {2, 3} };
	Line_seg ls2 = { {-1, -1}, {1, 2} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, false);
}

TEST(Int_LineSegs, NotInt_Parallel) {
	Line_seg ls1 = { {-1, 1}, {4, 7} };
	Line_seg ls2 = { {0, 2}, {5, 8} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, false);
}

TEST(Int_LineSegs, NotInt_OnLine) {
	Line_seg ls1 = { {-2, 6}, {-0.1, 4.1} };
	Line_seg ls2 = { {0.1, 3.9}, {2, 2} };
	bool res = intersect_ls(ls1, ls2);
	EXPECT_EQ(res, false);
}

TEST(Int_Trian, NoInt_1) {
	Triangle tr1 = { {0, 0}, {0, 3}, {3, 0} };
	Triangle tr2 = { {2, 2}, {2, 4}, {4, 2} };
	bool res = intersect_tr(tr1, tr2);
	EXPECT_EQ(res, false);
}

TEST(Int_Trian, NoInt_2) {
	Triangle tr1 = { {0, 0}, {0, 1}, {1, 0} };
	Triangle tr2 = { {2, 0}, {3, 0}, {3, 1} };
	bool res = intersect_tr(tr1, tr2);
	EXPECT_EQ(res, false);
}

TEST(Int_Trian, Int_by_point) {
	Triangle tr1 = { {0, 0}, {0, 1}, {1, 0} };
	Triangle tr2 = { {1, 0}, {2, 0}, {2, 1} };
	bool res = intersect_tr(tr1, tr2);
	EXPECT_EQ(res, true);
}

TEST(Int_Trian, Int_by_side) {
	Triangle tr1 = { {-1, 0}, {0, 0}, {0, 1} };
	Triangle tr2 = { {0, 0}, {0, 1}, {1, 0} };
	bool res = intersect_tr(tr1, tr2);
	EXPECT_EQ(res, true);
}

TEST(Int_Trian, Int_inside) {
	Triangle tr1 = { {0, 0}, {0, 5}, {7, 0} };
	Triangle tr2 = { {1, 1}, {1, 3}, {4, 1} };
	bool res = intersect_tr(tr1, tr2);
	EXPECT_EQ(res, true);
}

TEST(Int_Trian, Int_by_3int_sides) {
	Triangle tr1 = { {0, 0}, {6, 0}, {0, 6} };
	Triangle tr2 = { {-2, 4}, {4, 4}, {4, -2} };
	bool res = intersect_tr(tr1, tr2);
	EXPECT_EQ(res, true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}