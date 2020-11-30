#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

const double EPSILON = 0.000001;

namespace LinAl {

	template <typename T>
	class Matrix {
		int n;
		T* data;

	public:
		Matrix(int n_) : n(n_) { create_zero(n_); };
		template <typename S> Matrix(const Matrix<S>& that) noexcept { create_copying(that); };
		Matrix(const Matrix<T>& that) noexcept { create_copying(that); };
		Matrix(const std::vector<T>& data_list) { create_from_list(data_list); };
		Matrix(int dim, T det, int key) { create_random(dim, det, key); };

		int dim() const;
		T get(int i, int j) const;
		long double det() const;
		template <typename S> bool operator == (const Matrix<S>& that) const;
		Matrix<T> operator + (const Matrix<T>& that) const;
		void operator += (const Matrix<T>& that);
		void operator -= (const Matrix<T>& that);
		Matrix<T> operator - (const Matrix<T>& that) const;
		Matrix<T> operator * (const Matrix<T>& that) const;
		void operator *= (const Matrix<T>& that);
		Matrix<T> operator * (T k) const;
		void operator *= (T k);
		void operator = (const Matrix<T>& that);
		void print() const;
		void LUP(int& swaps);
		~Matrix();

	private:
		template <typename S> void set_from_matr(const Matrix<S>& that);
		void create_zero(int dim);
		void create_singular(int dim);
		template <typename S> void create_copying(const Matrix<S>& that);
		void create_from_list(const std::vector<T>& data_list);
		void create_random(int dim, T det, int key);
		void swap_rows(int r1, int r2);
		void set(int i, int j, T val);
		void add_row_to_row(int row1, int row2, int a);
		void mem_init(int dim);
	};

	//get dimension of matrix
	template <typename T>
	int Matrix<T>::dim() const
	{
		return n;
	}

	//get element from matrix 
	template <typename T>
	T Matrix<T>::get(int i, int j) const
	{
		return data[i * n + j];
	}

	//get determinant of matrix
	template <typename T>
	long double Matrix<T>::det() const
	{
		long double a;
		long double res = 1;
		int swaps = 0;
		Matrix<long double> U{ *this };
		U.LUP(swaps);
		for (int i = 0; i < n; i++)
		{
			a = U.get(i, i);
			res *= a;
		}
		if (swaps == 1)
			res *= -1;
		
		return res;
	}

	//operator ==
	template <typename T> template <typename S>
	bool Matrix<T>::operator == (const Matrix<S>& that) const
	{
		if (n != that.dim())
			return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (fabs(get(i, j) - that.get(i, j)) > EPSILON)
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
		if (n == that.dim())
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					set(i, j, get(i, j) + that.get(i, j));
	}

	//operator *= for num
	template <typename T>
	void Matrix<T>::operator *= (T k)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				set(i, j, get(i, j) * k);
	}

	//operator * for num (num on the right side)
	template <typename T>
	Matrix<T> Matrix<T>::operator * (T k) const
	{
		Matrix<T> tmp{ *this };
		tmp *= k;
		return tmp;
	}

	//operator * for num (num on the left side)
	template <typename T>
	Matrix<T> operator * (T k, const Matrix<T>& matr) { return matr * k; }

	//operator *= for matrix
	template <typename T>
	void Matrix<T>::operator *= (const Matrix<T>& that)
	{
		std::vector<T> new_row;
		new_row.resize(that.dim());
		//Matrix<T> tmp{ *this };
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				//T sum = 0;
				new_row[j] = 0;
				for (int k = 0; k < n; k++)
					new_row[j] += get(i, k) * that.get(k, j);
			}
			for (int j = 0; j < n; j++)
				set(i, j, new_row[j]);
		}
	}

	//operator * for matrix
	template <typename T>
	Matrix<T> Matrix<T>::operator * (const Matrix<T>& that) const
	{
		Matrix<T> tmp{ *this };
		tmp *= that;
		return tmp;
	}

	//operator -=
	template <typename T>
	void Matrix<T>::operator -= (const Matrix<T>& that)
	{
		operator+=(that * (-1));
	}

	//operator -
	template <typename T>
	Matrix<T> Matrix<T>::operator - (const Matrix<T>& that) const
	{
		Matrix tmp{ *this };
		tmp -= that;
		return tmp;
	}

	//set matrix, both matrix must have the same sizes and be initialized (only copying elements)
	template <typename T> template <typename S>
	void Matrix<T>::set_from_matr(const Matrix<S>& that)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				set(i, j, static_cast<T>(that.get(i, j)));
			}
	}

	//operator =
	template <typename T>
	void Matrix<T>::operator = (const Matrix<T>& that)
	{
		if (n != that.dim())
		{
			delete[] data;
			mem_init(that.dim());
			n = that.dim();
		}
		set_from_matr(that);
	}

	//create zero matrix (with mem init)
	template <typename T>
	void Matrix<T>::create_zero(int dim)
	{
		mem_init(dim);
		n = dim;
	}

	//create singular matrix = diag {1, ..., 1}
	template <typename T>
	void Matrix<T>::create_singular(int dim)
	{
		n = dim;
		mem_init(dim);
		for (int i = 0; i < dim; i++)
			set(i, i, 1);
	}

	//create by copying from matrix
	template <typename T>
	template <typename S>
	void Matrix<T>::create_copying(const Matrix<S>& that)
	{
		n = that.dim();
		mem_init(that.dim());
		set_from_matr(that);
	}

	//create by copying from list of data
	template <typename T>
	void Matrix<T>::create_from_list(const std::vector<T>& data_list)
	{
		n = sqrt(data_list.size());
		mem_init(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				set(i, j, data_list[i * n + j]);
	}

	//create random matrix with dim and det (using key, key = 0 for fully random)
	template <typename T>
	void Matrix<T>::create_random(int dim, T det, int key)
	{
		create_singular(dim);
		set(0, 0, det);
		if (key == 0)
			key = time(0);
		srand(key);
		int actions_count = dim * 3;
		for (int i = 0; i < actions_count; i++)
		{
			int a = rand() % 7 - 3;
			int row1 = rand() % dim;
			int row2 = rand() % dim;
			if ((row1 != row2)&&(a != 0))
				add_row_to_row(row1, row2, a);
		}
	}

	//set elem
	template <typename T>
	void Matrix<T>::set(int i, int j, T val)
	{
		data[i * n + j] = val;
	}

	//print matrix
	template <typename T>
	void Matrix<T>::print() const
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				std::cout << get(i, j) << " ";
			std::cout << std::endl;
		}
	}

	//swap rows
	template <typename T>
	void Matrix<T>::swap_rows(int r1, int r2)
	{
		for (int j = 0; j < n; j++)
		{
			T temp = get(r1, j);
			set(r1, j, get(r2, j));
			set(r2, j, temp);
		}
	}

	//LUP decomposition, matrix become L + U - E
	template<>
	void Matrix<long double>::LUP(int& swaps)
	{
		for (int i = 0; i < n; i++) {
			long double major_val = 0;
			int major_row = -1;
			for (int row = i; row < n; row++) {
				if (fabs(get(row, i)) > major_val) {
					major_val = fabs(get(row, i));
					major_row = row;
				}
			}
			if (major_val != 0) {
				if (major_row != i)
				{
					swap_rows(major_row, i);
					swaps = (swaps + 1) % 2;
				}
				for (int j = i + 1; j < n; j++) {
					set(j, i, get(j, i) / get(i, i));
					for (int k = i + 1; k < n; k++)
						set(j, k, get(j, k) - get(j, i) * get(i, k));
				}
			}
		}
	}

	//destructor
	template <typename T>
	Matrix<T>::~Matrix()
	{
		delete[] data;
	}

	// row1 += row2 * a
	template <typename T>
	void Matrix<T>::add_row_to_row(int row1, int row2, int a)
	{
		for (int i = 0; i < n; i++)
			set(row1, i, get(row2, i) * a + get(row1, i));
	}

	//initialize memory with "new" and set all elements 0
	template <typename T>
	void Matrix<T>::mem_init(int dim)
	{
		data = new T[dim * dim]{ 0 };
	}
}