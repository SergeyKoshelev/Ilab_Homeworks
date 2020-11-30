#include "pch.h"
#include "../../Matrix/Matrix.h"
#include <vector>

using type = int;
using type1 = long double;

const double RES_EPSILON = 0.1;

TEST(matr_ops, plus_plus) {
	using namespace LinAl;
	std::vector<int> dataA = { 1, 0, 0, 1 };
	std::vector<int> dataB = { 0, 1, 1, 0 };
	std::vector<int> dataC = { 1, 1, 1, 1 };
	std::vector<int> data_true = { 2, 2, 2, 2 };
	Matrix<int> A{ dataA };
	Matrix<int> B{ dataB };
	Matrix<int> C{ dataC };
	Matrix<int> matr_true{ data_true };
	Matrix<int> res = A + B + C;
	bool check = (res == matr_true);
	EXPECT_EQ(check, true);
}

TEST(matr_ops, minus_minus) {
	using namespace LinAl;
	std::vector<int> dataA = { -1, 0, 0, -1 };
	std::vector<int> dataB = { 0, 1, 1, 0 };
	std::vector<int> dataC = { 1, 1, 1, 1 };
	std::vector<int> data_true = { -2, -2, -2, -2 };
	Matrix<int> A{ dataA };
	Matrix<int> B{ dataB };
	Matrix<int> C{ dataC };
	Matrix<int> matr_true{ data_true };
	Matrix<int> res = A - B - C;
	bool check = (res == matr_true);
	EXPECT_EQ(check, true);
}

TEST(matr_ops, mult_mult_num) {
	using namespace LinAl;
	std::vector<int> data = { 1, 2, 3, 4 };
	std::vector<int> data_true = { -3, -6, -9, -12 };
	int k1 = 3;
	int k2 = -1;
	Matrix<int> matr_true{ data_true };
	Matrix<int> matr{ data };
	Matrix<int> res = k1 * matr * k2;
	bool check = (res == matr_true);
	EXPECT_EQ(check, true);
}

TEST(matr_ops, assign_dif_sizes) {
	using namespace LinAl;
	std::vector<int> data1 = { 1, 2, 3, 4 };
	std::vector<int> data2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix<int> matr1{ data1 };
	Matrix<int> matr2{ data2 };
	Matrix<int> res1{ data1 };
	Matrix<int> res2{ data2 };
	res1 = matr2;
	res2 = matr1;
	bool check = ((res1 == matr2) && (res2 == matr1));
	EXPECT_EQ(check, true);
}

TEST(matr_ops, mult_mult_matr) {
	using namespace LinAl;
	std::vector<int> dataA = { 1, 2, 0, -1, 3, -2, 0, 1, -3 };
	std::vector<int> dataB = { 3, -1, 1, 0, 2, -2, 3, 1, 0 };
	std::vector<int> dataC = { 1, 1, -2, -1, 0, 3, 0, 2, -3 };
	std::vector<int> data_true = { 0, -3, 12, -14, -23, 54, -8, -13, 21 };
	Matrix<int> A{ dataA };
	Matrix<int> B{ dataB };
	Matrix<int> C{ dataC };
	Matrix<int> matr_true{ data_true };
	Matrix<int> res = A * B * C;
	bool check = (res == matr_true);
	EXPECT_EQ(check, true);
}

TEST(matr_ops, 2ops) {
	using namespace LinAl;
	std::vector<type> dataA = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<type> dataB = { 1, 4, 7, 2, 5, 8, 3, 6, 9 };
	std::vector<type1> dataC = { 7, 16, 25, 16, 38.5, 61, 25, 61, 97 };
	Matrix<type> A{ dataA };
	Matrix<type> B{ dataB };
	Matrix<type1> C{ dataC };
	Matrix<type1> res = A * B;
	res *= 0.5;
	bool check = (res == C);
	EXPECT_EQ(check, true);
}

TEST(matr_ops, many_ops) {
	using namespace LinAl;
	std::vector<int> dataA = {1, 1, 1, 1};
	std::vector<int> dataB = {0, 2, -1, 1 };
	std::vector<long double> dataC = { 5, -7, 3, -1  };
	Matrix<int> A{ dataA };
	Matrix<int> B{ dataB };
	Matrix<long double> C{ dataC };
	Matrix<long double> res = (A + B * 2) * -1 * B ;
	bool check = (res == C);
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