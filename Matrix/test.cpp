#include "pch.h"
#include "../../Matrix/Matrix.h"
#include <vector>

typedef long double type;

TEST(matr_ops, case1) {
	using namespace LinAl;
	int dim = 3;
	Matrix<type> matr1{ dim };
	Matrix<type> matr2{ dim };
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
		{
			matr1.set_elem(i, j, i * 3.0 + j + 1);
			matr2.set_elem(i, j, j * 3.0 + i + 1);
		}
	Matrix<type> matr3{ dim };
	matr3.set_elem(0, 0, 14); matr3.set_elem(0, 1, 32); matr3.set_elem(0, 2, 50);
	matr3.set_elem(1, 0, 32); matr3.set_elem(1, 1, 77); matr3.set_elem(1, 2, 122);
	matr3.set_elem(2, 0, 50); matr3.set_elem(2, 1, 122); matr3.set_elem(2, 2, 194);
	Matrix<type> res = matr1 * matr2;
	bool check = (res == matr3);
  EXPECT_EQ(check, true);
}

TEST(deter2x2, case1)
{
	using namespace LinAl;
	int dim = 2;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 2); matr.set_elem(0, 1, 3);
	matr.set_elem(1, 0, 1); matr.set_elem(1, 1, 4);
	type deter = matr.det();
	EXPECT_EQ(deter, 5);
}

TEST(deter2x2, case2)
{
	using namespace LinAl;
	int dim = 2;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 1); matr.set_elem(0, 1, 4);
	matr.set_elem(1, 0, 2); matr.set_elem(1, 1, 3);
	type deter = matr.det();
	EXPECT_EQ(deter, -5);
}

TEST(deter2x2, case3)
{
	using namespace LinAl;
	int dim = 2;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 1); matr.set_elem(0, 1, 4);
	matr.set_elem(1, 0, 2); matr.set_elem(1, 1, 8);
	type deter = matr.det();
	EXPECT_EQ(deter, 0);
}

TEST(deter2x2, zero_infinity_1)
{
	using namespace LinAl;
	int dim = 2;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 0); matr.set_elem(0, 1, 1);
	matr.set_elem(1, 0, 2); matr.set_elem(1, 1, 8);
	type deter = matr.det();
	EXPECT_EQ(deter, -2);
}

TEST(deter2x2, zero_infinity_2)
{
	using namespace LinAl;
	int dim = 2;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 1); matr.set_elem(0, 1, 4);
	matr.set_elem(1, 0, 2); matr.set_elem(1, 1, 3);
	type deter = matr.det();
	EXPECT_EQ(deter, -5);
}

TEST(deter2x2, zero_row)
{
	using namespace LinAl;
	int dim = 2;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 0); matr.set_elem(0, 1, 0);
	matr.set_elem(1, 0, 2); matr.set_elem(1, 1, 3);
	type deter = matr.det();
	EXPECT_EQ(deter, 0);
}

TEST(deter5x5, case1)
{
	using namespace LinAl;
	int dim = 5;
	Matrix<type> matr{ dim };
	matr.set_elem(0, 0, 1); matr.set_elem(0, 1, 2); matr.set_elem(0, 2, 3); matr.set_elem(0, 3, 4); matr.set_elem(0, 4, 5);
	matr.set_elem(1, 0, -2); matr.set_elem(1, 1, -5); matr.set_elem(1, 2, 2); matr.set_elem(1, 3, -8); matr.set_elem(1, 4, 1);
	matr.set_elem(2, 0, 0); matr.set_elem(2, 1, 7); matr.set_elem(2, 2, -7); matr.set_elem(2, 3, 9); matr.set_elem(2, 4, 2);
	matr.set_elem(3, 0, 1); matr.set_elem(3, 1, 1); matr.set_elem(3, 2, 1); matr.set_elem(3, 3, 0); matr.set_elem(3, 4, -1);
	matr.set_elem(4, 0, 4); matr.set_elem(4, 1, 5); matr.set_elem(4, 2, -3); matr.set_elem(4, 3, -2); matr.set_elem(4, 4, 1);
	type deter = matr.det();
	EXPECT_EQ(deter, 1619);
}