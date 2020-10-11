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
		bool point_on_plane(const Point& point);
		bool inter_2D(const Triangle& that);
		bool parallel(const Triangle& that);

	private:

		void create_plane();
	};

	class Line {
		double x0, y0, z0;
		double ax, ay, az;
	public:
		Line(const Triangle::Point& p1, const Triangle::Point& p2) : x0(p1.x), y0(p1.y), z0(p1.z), ax(p1.x-p2.x), ay(p1.y-p2.y), az(p1.z-p2.z) {};

		void init(const Triangle& tr1, const Triangle& tr2);
		Line(const Triangle& tr1, const Triangle& tr2)
		{	
			//under construction
			init(tr1, tr2);
		}
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

	//check if 2 triangles intersect (main with that)
	bool Triangle::intersection(const Triangle& that)
	{
		//under construction
		bool A_on_plane = this->point_on_plane(that.A);
		bool B_on_plane = this->point_on_plane(that.B);
		bool C_on_plane = this->point_on_plane(that.C);

		if (A_on_plane && B_on_plane && C_on_plane)
			return inter_2D(that);//not ready
	
		if (parallel(that))
			return false;

		//planes intersect

		return true;
	}

	//check if point is on plane
	bool Triangle::point_on_plane(const Point& point)
	{
		double temp = point.x * this->a + point.y * this->b + point.z * this->c + d;
		return (fabs(temp) < EPSILON);
	}

	//check if 2 triangles are parallel
	bool Triangle::parallel(const Triangle& that)
	{
		if (fabs(this->b * that.c - this->c * that.b) < EPSILON)
			if (fabs(this->b * that.a - this->a * that.b) < EPSILON)
				if (fabs(this->a * that.c - this->c * that.a) < EPSILON)
					return this->point_on_plane(that.A);
		return false;
	}

	//intersection on plane
	bool Triangle::inter_2D(const Triangle& that)
	{
		//under construction
	}

	//determinant of matrix 2x2
	double Triangle::det2x2(double a11, double a12, double a21, double a22)
	{
		return a11 * a22 - a12 * a21;
	}

	void Line::init(const Triangle& tr1, const Triangle& tr2)
	{
		this->ax = tr1.b * tr2.c - tr1.c * tr2.b;
		ay = tr1.c * tr2.a - tr1.a * tr2.c;
		az = tr1.a * tr2.b - tr1.b * tr2.a;
		//find point on a line

		if ((fabs(tr1.a) < EPSILON) && (fabs(tr2.a) < EPSILON)) //a1 != 0 && a2 != 0
		{
			double temp_b = tr1.b * tr2.a - tr2.b * tr1.a;
			double temp_c = tr1.c * tr2.a - tr2.c * tr1.a;
			double temp_d = tr1.d * tr2.a - tr2.d * tr1.a;

			if (fabs(temp_b) < EPSILON)
			{
				z0 = -temp_d / temp_c;
				y0 = z0;
				x0 = -(tr1.d + tr1.c * z0 + tr1.b * y0);
			}
			else
			{
				z0 = 0;
				y0 = -temp_d / temp_b;
				x0 = x0 = -(tr1.d + tr1.b * y0);
			}
		}
		else if ((fabs(tr1.b) < EPSILON) && (fabs(tr2.b) < EPSILON)) //b1 != 0 && b2 != 0
		{
			double temp_a = tr1.a * tr2.b - tr2.a * tr1.b;
			double temp_c = tr1.c * tr2.b - tr2.c * tr1.b;
			double temp_d = tr1.d * tr2.b - tr2.d * tr1.b;

			if (fabs(temp_a) < EPSILON)
			{
				z0 = -temp_d / temp_c;
				x0 = z0;
				y0 = -(tr1.d + tr1.c * z0 + tr1.a * x0);
			}
			else
			{
				z0 = 0;
				x0 = -temp_d / temp_a;
				y0 = -(tr1.d + tr1.a * x0);
			}
		}
		else if ((fabs(tr1.c) < EPSILON) && (fabs(tr2.c) < EPSILON)) //c1 != 0 && c2 != 0
		{
			double temp_a = tr1.a * tr2.c - tr2.a * tr1.c;
			double temp_b = tr1.b * tr2.c - tr2.b * tr1.c;
			double temp_d = tr1.d * tr2.c - tr2.d * tr1.c;

			if (fabs(temp_a) < EPSILON)
			{
				y0 = -temp_d / temp_b;
				x0 = y0;
				z0 = -(tr1.d + tr1.b * y0 + tr1.a * x0);
			}
			else
			{
				y0 = 0;
				x0 = -temp_d / temp_a;
				z0 = -(tr1.d + tr1.a * x0);
			}
		}
		else
		{

		}
	}
}