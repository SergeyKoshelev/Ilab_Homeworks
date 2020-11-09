#pragma once
#include <vector>
#include <iostream>
#include <cmath>

const double EPSILON = 0.000001;

namespace LinAl {

	template <typename T>
	class Matrix {
		int n;
		std::vector<std::vector<T>> data;

	public:
		Matrix(int n_) : n(n_) { create_empty(); };
		int get_dim() const;
		void set_elem(int i, int j, T val);
		T get_elem(int i, int j) const;
		T det() const;
		bool operator == (const Matrix<T>& that) const;
		Matrix<T> operator + (const Matrix<T>& that) const;
		void operator += (const Matrix<T>& that);
		Matrix<T> operator * (const Matrix<T>& that) const;
		void operator *= (const Matrix<T>& that);
		Matrix<T> operator * (T k) const;
		void operator *= (T k);
		void operator = (const Matrix<T>& that);
		void print();

	private:
		Matrix<T> prepare_for_decomp() const;
		void set_matr(const Matrix<T>& that);
		Matrix<T> LU_decomp() const;
		void create_empty();
		void swap_rows(int r1, int r2);
		Matrix<T> LUP(int& swaps) const;
	};

	//get dimension of matrix
	template <typename T>
	int Matrix<T>::get_dim() const
	{
		return n;
	}

	//get element from matrix 
	template <typename T>
	T Matrix<T>::get_elem(int i, int j) const
	{
		return data[i][j];
	}

	//get determinant of matrix
	template <typename T>
	T Matrix<T>::det() const
	{
		T a;
		T res = 1;
		int swaps = 0;
		Matrix<T> U = LUP(swaps);
		for (int i = 0; i < n; i++)
		{
			a = U.get_elem(i, i);
			res *= a;
		}
		if (swaps == 1)
			res *= -1;
		return res;
	}

	//operator ==
	template <typename T>
	bool Matrix<T>::operator == (const Matrix<T>& that) const
	{
		if (n != that.get_dim())
			return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (fabs(data[i][j] - that.get_elem(i, j)) > EPSILON)
					return false;
		return true;
	}

	//operator +
	template <typename T>
	Matrix<T> Matrix<T>::operator + (const Matrix<T>& that) const
	{
		Matrix tmp{ *this };
		tmp += that;
		return tmp;
	}

	//operator +=
	template <typename T>
	void Matrix<T>::operator += (const Matrix<T>& that)
	{
		if (n == that.get_dim())
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					data[i][j] += that.get_elem(i, j);
	}

	//operator *= for num
	template <typename T>
	void Matrix<T>::operator *= (T k)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				data[i][j] *= k;
	}

	//operator * for num
	template <typename T>
	Matrix<T> Matrix<T>::operator * (T k) const
	{
		Matrix tmp{ *this };
		tmp *= k;
		return tmp;
	}

	//operator *= for matrix
	template <typename T>
	void Matrix<T>::operator *= (const Matrix<T>& that)
	{
		Matrix tmp{ *this };
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				T sum = 0;
				for (int k = 0; k < n; k++)
					sum += tmp.get_elem(i, k) * that.get_elem(k, j);
				data[i][j] = sum;
			}
		//set_matr(tmp);
	}

	//operator * for matrix
	template <typename T>
	Matrix<T> Matrix<T>::operator * (const Matrix<T>& that) const
	{
		Matrix tmp{ *this };
		tmp *= that;
		return tmp;
	}

	//set matrix
	template <typename T>
	void Matrix<T>::set_matr(const Matrix<T>& that)
	{
		n = that.get_dim();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				data[i][j] = that.get_elem(i, j);
	}

	//operator =
	template <typename T>
	void Matrix<T>::operator = (const Matrix<T>& that)
	{
		set_matr(that);
	}

	//preparing for LU-decomp (not created)
	template <typename T>
	Matrix<T> Matrix<T>::prepare_for_decomp() const
	{
		//under constuction
		Matrix<T> temp = { n };
		return *this;
	}

	//LU decomposition, return U, diag(L) = {1} (bad function, cant solve infinity problem, use LUP)
	template <typename T>
	Matrix<T> Matrix<T>::LU_decomp() const
	{
		int swaps = 0;
		LUP(swaps);
		Matrix<T> L = { n };
		for (int i = 0; i < n; i++)
			L.set_elem(i, i, 1);
		Matrix<T> U = { n };
		T sum_u, sum_l;
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
	template <typename T>
	void Matrix<T>::create_empty()
	{
		std::vector<T> line;
		for (int i = 0; i < n; i++)
			line.push_back(0);
		for (int i = 0; i < n; i++)
			data.push_back(line);
	}

	//set elem
	template <typename T>
	void Matrix<T>::set_elem(int i, int j, T val)
	{
		data[i][j] = val;
	}

	//print matrix
	template <typename T>
	void Matrix<T>::print()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				std::cout << data[i][j] << " ";
			std::cout << std::endl;
		}
	}

	//swap rows
	template <typename T>
	void Matrix<T>::swap_rows(int r1, int r2)
	{
		for (int i = 0; i < n; i++)
		{
			T temp = data[r1][i];
			data[r1][i] = data[r2][i];
			data[r2][i] = temp;
		}
	}

	//LUP decomposition, return L + U - E
	template <typename T>
	Matrix<T> Matrix<T>::LUP(int& swaps) const
	{
		Matrix<T> C = { *this };

		for (int i = 0; i < n; i++) {
			T major_val = 0;
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