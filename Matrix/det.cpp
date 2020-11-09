#include <iostream>
#include "Matrix.h"
#include <vector>

using type = long double;

int main()
{
	using namespace LinAl;
	int n;
	std::cout << "Input dimension of matrix NxN" << std::endl;
	std::cin >> n;

	std::vector<type> data; 
	double temp;

	std::cout << "Input elements of matrix" << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cin >> temp;
			data.push_back(temp);
		}
	}

	Matrix<type> matrix{ data };

	double det = matrix.det();
	std::cout << "Determinant is: " << det << std::endl;
}