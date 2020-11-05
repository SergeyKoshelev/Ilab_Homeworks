#pragma once
#include <vector>
#include <iostream>
#include <cmath>

const double EPSILON = 0.00001;

namespace LinAl {

	class Matrix {
		int n;
		std::vector<std::vector<double>> data;

	public:
		Matrix(int n_) : n(n_) { create_empty(); };
		int get_dim() const;
		void set_elem(int i, int j, double val);
		double get_elem(int i, int j) const;
		double det() const;
		bool operator == (const Matrix& that) const;
		Matrix operator + (const Matrix& that) const;
		void operator += (const Matrix& that);
		Matrix operator * (const Matrix& that) const;
		void operator *= (const Matrix& that);
		Matrix operator * (double k) const;
		void operator *= (double k);
		void operator = (const Matrix& that);
		void print();

	private:
		Matrix prepare_for_decomp() const;
		void set_matr(const Matrix& that);
		Matrix LU_decomp() const;
		void create_empty();
		void swap_rows(int r1, int r2);
		Matrix LUP(int& swaps) const;
	};

	//get dimension of matrix
	int Matrix::get_dim() const
	{
		return n;
	}

	//get element from matrix 
	double Matrix::get_elem(int i, int j) const
	{
		return data[i][j];
	}

	//get determinant of matrix
	double Matrix::det() const
	{
		double a;
		double res = 1;
		int swaps = 0;
		Matrix U = LUP(swaps);
		for (int i = 0; i < n; i++)
		{
			a = U.get_elem(i, i);
			if (fabs(a) < EPSILON)
				return 0;
			res *= a;
		}
		if (swaps == 1)
			res *= -1;
		return res;
	}

	//operator == 
	bool Matrix::operator == (const Matrix& that) const
	{
		if (n != that.get_dim())
			return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (data[i][j] != that.get_elem(i, j))
					return false;
		return true;
	}

	//operator +
	Matrix Matrix::operator + (const Matrix& that) const
	{
		Matrix tmp{ *this };
		tmp += that;
		return tmp;
	}

	//operator +=
	void Matrix::operator += (const Matrix& that)
	{
		if (n == that.get_dim())
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					data[i][j] += that.get_elem(i, j);
	}

	//operator *= for num
	void Matrix::operator *= (double k)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				data[i][j] *= k;
	}

	//operator * for num
	Matrix Matrix::operator * (double k) const
	{
		Matrix tmp{ *this };
		tmp *= k;
		return tmp;
	}

	//operator *= for matrix
	void Matrix::operator *= (const Matrix& that)
	{
		Matrix tmp{ *this };
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				double sum = 0;
				for (int k = 0; k < n; k++)
					sum += tmp.get_elem(i, k) * that.get_elem(k, j);
				data[i][j] = sum;
			}
		//set_matr(tmp);
	}

	//operator * for matrix
	Matrix Matrix::operator * (const Matrix& that) const
	{
		Matrix tmp{ *this };
		tmp *= that;
		return tmp;
	}

	//set matrix
	void Matrix::set_matr(const Matrix& that)
	{
		n = that.get_dim();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				data[i][j] = that.get_elem(i, j);
	}

	//operator =
	void Matrix::operator = (const Matrix& that)
	{
		set_matr(that);
	}

	//preparing for LU-decomp (not created)
	Matrix Matrix::prepare_for_decomp() const
	{
		//under constuction
		Matrix temp = { n };
		return *this;
	}

	//LU decomposition, return U, diag(L) = {1} (bad function, cant solve infinity problem, use LUP)
	Matrix Matrix::LU_decomp() const
	{
		int swaps = 0;
		LUP(swaps);
		Matrix L = { n };
		for (int i = 0; i < n; i++)
			L.set_elem(i, i, 1);
		Matrix U = { n };
		double sum_u, sum_l;
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				sum_u = 0;
				for (int k = 0; k < i; k++)
					sum_u += U.get_elem(k, j) * L.get_elem(i, k);
				U.set_elem(i, j, data[i][j] - sum_u);
			}
			for (int j = i + 1; j < n; j++)
			{
				sum_l = 0;
				for (int k = 0; k < i; k++)
					sum_l += U.get_elem(k, i) * L.get_elem(j, k);
				L.set_elem(j, i, (data[j][i] - sum_l) / U.get_elem(i, i));
			}
		}
		return U;
	}

	//create empty matrix
	void Matrix::create_empty()
	{
		std::vector<double> line;
		for (int i = 0; i < n; i++)
			line.push_back(0);
		for (int i = 0; i < n; i++)
			data.push_back(line);
	}

	//set elem
	void Matrix::set_elem(int i, int j, double val)
	{
		data[i][j] = val;
	}

	//print matrix
	void Matrix::print()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				std::cout << data[i][j] << " ";
			std::cout << std::endl;
		}
	}

	//swap rows
	void Matrix::swap_rows(int r1, int r2)
	{
		for (int i = 0; i < n; i++)
		{
			double temp = data[r1][i];
			data[r1][i] = data[r2][i];
			data[r2][i] = temp;
		}
	}

	//LUP decomposition, return L + U - E
	Matrix Matrix::LUP(int& swaps) const 
	{
		Matrix C = { *this };

		for (int i = 0; i < n; i++) {
			double major_val = 0;
			int major_row = -1;
			for (int row = i; row < n; row++) {
				if (fabs(C.get_elem(row, i)) > major_val) {
					major_val = fabs(C.get_elem(row, i));
					major_row = row;
				}
			}
			if (major_val != 0) {
				if (major_row != i)
				{
					C.swap_rows(major_row, i);
					swaps = (swaps + 1) % 2;
				}
				for (int j = i + 1; j < n; j++) {
					C.set_elem(j, i, C.get_elem(j, i) / C.get_elem(i, i));
					for (int k = i + 1; k < n; k++)
						C.set_elem(j, k, C.get_elem(j, k) - C.get_elem(j, i) * C.get_elem(i, k));
				}
			}
		}
		return C;
	}
}