#pragma once

#include <iostream>
#include <cmath>

const double EPSILON = 0.000001;


namespace Triangles {

	class Triangle {
	public:
		class Point {
		public:
			double x, y, z;

			Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};

			bool operator == (const Point& that) const;
		};

		int id;
		Point A, B, C;
		double a, b, c, d;

	public:
		Triangle(int id_, const Point& A_, const Point& B_, const Point& C_) : id(id_), A(A_), B(B_), C(C_) { create_plane(); };

		bool is_triangle() const;
		bool in_right_side(const Triangle& that);
		bool in_left_side(const Triangle& that);
		int get_id();
		double det2x2(double a11, double a12, double a21, double a22);
		bool intersection(const Triangle& that);

	private:

		void create_plane();
	};

	//operator == for points
	bool Triangle::Point::operator == (const Point& that) const
	{
		if (std::fabs(x - that.x) < EPSILON)
			if (std::fabs(y - that.y) < EPSILON)
				if (std::fabs(y - that.y) < EPSILON)
					return true;

		return false;
	}

	//get triangle id
	int Triangle::get_id()
	{
		return this->id;
	}

	//check is triangle
	bool Triangle::is_triangle() const
	{
		if (this->A == this->C)
			return false;
		if (this->A == this->B)
			return false;
		if (this->C == this->B)
			return false;
		return true;

	}

	//check right side 
	bool Triangle::in_right_side(const Triangle& that)
	{
		double res1 = a * that.A.x + b * that.A.y + c * that.A.z + d;
		double res2 = a * that.B.x + b * that.B.y + c * that.B.z + d;
		double res3 = a * that.C.x + b * that.C.y + c * that.C.z + d;

		if ((res1 > EPSILON) && (res2 > EPSILON) && (res3 > EPSILON))
			return true;

		return false;
	}

	//check left side 
	bool Triangle::in_left_side(const Triangle& that)
	{
		double res1 = a * that.A.x + b * that.A.y + c * that.A.z + d;
		double res2 = a * that.B.x + b * that.B.y + c * that.B.z + d;
		double res3 = a * that.C.x + b * that.C.y + c * that.C.z + d;

		if ((res1 < EPSILON) && (res2 < EPSILON) && (res3 < EPSILON))
			return true;

		return false;
	}

	//create plane on points
	void Triangle::create_plane()
	{
		double det1 = det2x2(this->B.y - this->A.y, this->B.z - this->A.z, this->C.y - this->A.y, this->C.z - this->A.z);
		double det2 = det2x2(this->B.x - this->A.x, this->B.z - this->A.z, this->C.x - this->A.x, this->C.z - this->A.z);
		double det3 = det2x2(this->B.x - this->A.x, this->B.y - this->A.y, this->C.x - this->A.x, this->C.y - this->A.y);

		this->a = det1;
		this->b = -det2;
		this->c = det3;
		this->d = -det1 * this->A.x + det2 * this->A.y - det3 * this->A.z;
	}

	bool Triangle::intersection(const Triangle& that)
	{
		return true;
	}

	double Triangle::det2x2(double a11, double a12, double a21, double a22)
	{
		return a11 * a22 - a12 * a21;
	}
}