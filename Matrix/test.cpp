#include "pch.h"
#include "../../Matrix/Matrix.h"
#include <vector>

using type = long double;

const double RES_EPSILON = 0.1;

TEST(matr_ops, case1) {
	using namespace LinAl;
	int dim = 3;
	std::vector<type> data1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<type> data2 = { 1, 4, 7, 2, 5, 8, 3, 6, 9 };
	std::vector<type> data3 = { 7, 16, 25, 16, 38.5, 61, 25, 61, 97 };
	Matrix<type> matr1{ data1 };
	Matrix<type> matr2{ data2 };
	Matrix<type> matr3{ data3 };
	Matrix<type> res = matr1 * matr2;
	res *= 0.5;
	bool check = (res == matr3);
  EXPECT_EQ(check, true);
}

TEST(deter2x2, case1)
{
	using namespace LinAl;
	int dim = 2;
	std::vector<type> data = { 2, 3, 1, 4 };
	Matrix<type> matr{ data };
	type deter = matr.det();
	EXPECT_EQ(deter, 5);
}

TEST(deter2x2, case2)
{
	using namespace LinAl;
	int dim = 2;
	std::vector<type> data = { 1, 4, 2, 8 };
	Matrix<type> matr{ data };
	type deter = matr.det();
	EXPECT_EQ(deter, 0);
}

TEST(deter2x2, zero_infinity_1)
{
	using namespace LinAl;
	int dim = 2;
	std::vector<type> data = { 0, 1, 2, 8 };
	Matrix<type> matr{ data };
	type deter = matr.det();
	EXPECT_EQ(deter, -2);
}

TEST(deter2x2, zero_infinity_2)
{
	using namespace LinAl;
	int dim = 2;
	std::vector<type> data = { 1, 4, 2, 3 };
	Matrix<type> matr{ data };
	type deter = matr.det();
	EXPECT_EQ(deter, -5);
}

TEST(deter2x2, zero_row)
{
	using namespace LinAl;
	int dim = 2;
	std::vector<type> data = { 0, 0, 2, 3 };
	Matrix<type> matr{ data };
	type deter = matr.det();
	EXPECT_EQ(deter, 0);
}

TEST(deter5x5, case1)
{
	using namespace LinAl;
	int dim = 5;
	std::vector<type> data = { 1, 2, 3, 4, 5, -2, -5, 2, -8, 1, 0, 7, -7, 9, 2, 1, 1, 1, 0, -1, 4, 5, -3, -2, 1 };
	Matrix<type> matr{ data };
	type deter = matr.det();
	EXPECT_EQ(deter, 1619);
}

TEST(random_matr, 2x2)
{
	using namespace LinAl;
	int dim = 2;
	type det = 20;
	int key = 10;
	Matrix<type> matr{ dim, det, key };
	bool res = fabs(det - matr.det()) < RES_EPSILON;
	EXPECT_EQ(true, res);
}

TEST(random_matr, 20x20)
{
	using namespace LinAl;
	int dim = 20;
	type det = 3;
	int key = 100;
	Matrix<type> matr{ dim, det, key };
	bool res = fabs(det - matr.det()) < RES_EPSILON;
	EXPECT_EQ(true, res);
}

TEST(random_matr, 50x50)
{
	using namespace LinAl;
	int dim = 50;
	type det = 7;
	int key = 31;
	Matrix<type> matr{ dim, det, key };
	bool res = fabs(det - matr.det()) < RES_EPSILON;
	EXPECT_EQ(true, res);
}

TEST(random_matr, 100x100)
{
	using namespace LinAl;
	int dim = 100;
	type det = -2;
	int key = 49;
	Matrix<type> matr{ dim, det, key };
	bool res = fabs(det - matr.det()) < RES_EPSILON;
	EXPECT_EQ(true, res);
}

TEST(random_matr, 1000x1000)
{
	using namespace LinAl;
	int dim = 1000;
	type det = -1;
	int key = 101;
	Matrix<type> matr{ dim, det, key };
	bool res = fabs(det - matr.det()) < RES_EPSILON;
	EXPECT_EQ(true, res);
}

TEST(random_matr, 1000x1000_fullrandom)
{
	using namespace LinAl;
	int dim = 1000;
	type det = -1;
	Matrix<type> matr{ dim, det, 0 };
	bool res = fabs(det - matr.det()) < RES_EPSILON;
	EXPECT_EQ(true, res);
}