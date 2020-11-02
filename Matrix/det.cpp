#include <iostream>
#include "Matrix.h"
#include <vector>

int main()
{
	using namespace LinAl;
	int n;
	std::cout << "Input dimension of matrix NxN" << std::endl;
	std::cin >> n;

	Matrix matrix{ n };
	double temp;

	std::cout << "Input elements of matrix" << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cin >> temp;
			matrix.set_elem(i, j, temp);
		}
	}

	double det = matrix.det();
	std::cout << "Determinant is: " << det << std::endl;
}