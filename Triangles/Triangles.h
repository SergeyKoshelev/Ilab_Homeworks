#pragma once

#include <iostream>
#include <cmath>

const double EPSILON = 0.000001;

namespace Triangles {

	class Point {
		double x, y, z;

	public:
		Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};

		bool operator == (const Point& that);
	};

	bool Point::operator == (const Point& that)
	{
		if (std::fabs(x - that.x) < EPSILON)
			if (std::fabs(y - that.y) < EPSILON)
				if (std::fabs(y - that.y) < EPSILON)
					return true;

		return false;
	}

}




namespace Triangles {

	class Triangle {

		int id;
		Point A, B, C;

	public:
		Triangle(int id_, const Point& A_, const Point& B_, const Point& C_) : id(id_), A(A_), B(B_), C(C_) {};

		bool is_triangle();
		bool in_right_side(const Triangle& that);
		bool in_left_side(const Triangle& that);

	private:

		void create_plane();
	};

	//check is triangle
	bool Triangle::is_triangle()
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
		//under construction
	}

	//check left side 
	bool Triangle::in_left_side(const Triangle& that)
	{
		//under construction
	}

	//create plane on points
	void Triangle::create_plane()
	{
		//under construction
	}
}