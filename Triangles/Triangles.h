#pragma once

#include <iostream>
#include <cmath>

const double EPSILON = 0.00000001;


namespace Triangles {

	class Triangle {
	public:
		class Point {
		public:
			double x, y, z;

			Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};

			bool operator == (const Point& that) const;

			bool between(const Point& p1, const Point& p2) const;
		};

		int id;
		Point A, B, C;
		double a, b, c, d;

	public:
		Triangle(int id_, const Point& A_, const Point& B_, const Point& C_) : id(id_), A(A_), B(B_), C(C_) { create_plane(); };

		bool is_triangle() const;
		bool in_right_side(const Triangle& that) const;
		bool in_left_side(const Triangle& that) const;
		int get_id() const;
		friend double det2x2(double a11, double a12, double a21, double a22);
		bool intersection(const Triangle& that) const;
		bool point_on_plane(const Point& point) const;
		bool inter_2D(const Triangle& that) const;
		bool parallel(const Triangle& that) const;
		bool point_inside(const Point& p) const;
		bool inter_line_segs(const Triangle& tr) const;
		void print_trian() const;

	private:

		void create_plane();
	};

	class Line {
		double x0, y0, z0;
		double ax, ay, az;
	public:
		Line(const Triangle::Point& p1, const Triangle::Point& p2) : x0(p1.x), y0(p1.y), z0(p1.z), ax(p1.x-p2.x), ay(p1.y-p2.y), az(p1.z-p2.z) {};
		Line(const Triangle& tr1, const Triangle& tr2)
		{
			init(tr1, tr2);
		}

		void init(const Triangle& tr1, const Triangle& tr2);
		Triangle::Point* line_inter(const Line& that);
		double get_ax() const;
		double get_ay() const;
		double get_az() const;
		double get_x0() const;
		double get_y0() const;
		double get_z0() const;
	};

	//determinant of matrix 2x2
	double det2x2(double a11, double a12, double a21, double a22)
	{
		return a11 * a22 - a12 * a21;
	}

	//operator == for points
	bool Triangle::Point::operator == (const Point& that) const
	{
		if (std::fabs(x - that.x) <= EPSILON)
			if (std::fabs(y - that.y) <= EPSILON)
				if (std::fabs(y - that.y) <= EPSILON)
					return true;

		return false;
	}

	//check if point is between 2 other points
	bool Triangle::Point::between(const Point& p1, const Point& p2) const
	{
		if ((x < (std::max(p1.x, p2.x) + EPSILON)) && (x > (std::min(p1.x, p2.x) - EPSILON)) &&
			(y < (std::max(p1.y, p2.y) + EPSILON)) && (y > (std::min(p1.y, p2.y) - EPSILON)) &&
			(z < (std::max(p1.z, p2.z) + EPSILON)) && (z > (std::min(p1.z, p2.z) - EPSILON)))
			return true;
		return false;
	}

	//get triangle id
	int Triangle::get_id() const
	{
		return id;
	}

	//check is triangle
	bool Triangle::is_triangle() const
	{
		if ((A == C)||(A == B)||(C == B))
			return false;
		return true;
	}

	//check right side 
	bool Triangle::in_right_side(const Triangle& that) const
	{
		double res1 = a * that.A.x + b * that.A.y + c * that.A.z + d;
		double res2 = a * that.B.x + b * that.B.y + c * that.B.z + d;
		double res3 = a * that.C.x + b * that.C.y + c * that.C.z + d;

		if ((res1 > EPSILON) && (res2 > EPSILON) && (res3 > EPSILON))
			return true;

		return false;
	}

	//check left side 
	bool Triangle::in_left_side(const Triangle& that) const
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
		double det1 = det2x2(B.y - A.y, B.z - A.z, C.y - A.y, C.z - A.z);
		double det2 = det2x2(B.x - A.x, B.z - A.z, C.x - A.x, C.z - A.z);
		double det3 = det2x2(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);

		a = det1;
		b = -det2;
		c = det3;
		d = -det1 * A.x + det2 * A.y - det3 * A.z;
	}

	//check if 2 triangles intersect (main with that)
	bool Triangle::intersection(const Triangle& that) const
	{
		//cant intersect 
		if (that.in_right_side(*this) || that.in_left_side(*this))
			return false;

		//check on 1 plane
		bool A_on_plane = point_on_plane(that.A);
		bool B_on_plane = point_on_plane(that.B);
		bool C_on_plane = point_on_plane(that.C);

		if (A_on_plane && B_on_plane && C_on_plane)
			return inter_2D(that);
	
		//check complex intersection on line
		return inter_line_segs(that);
	}

	//check if point is on plane
	bool Triangle::point_on_plane(const Point& point) const
	{
		double temp = point.x * a + point.y * b + point.z * c + d;
		return (fabs(temp) <= EPSILON);
	}

	//check if 2 triangles are parallel
	bool Triangle::parallel(const Triangle& that) const
	{
		if (fabs(b * that.c - c * that.b) <= EPSILON)
			if (fabs(b * that.a - a * that.b) <= EPSILON)
				if (fabs(a * that.c - c * that.a) <= EPSILON)
					return point_on_plane(that.A);
		return false;
	}

	//check if point is inside of triangle
	bool Triangle::point_inside(const Point& p) const
	{
		double v1_x = det2x2(p.y - A.y, p.z - A.z, B.y - A.y, B.z - A.z);
		double v1_y = - det2x2(p.x - A.x, p.z - A.z, B.x - A.x, B.z - A.z);
		double v1_z = det2x2(p.x - A.x, p.y - A.y, B.x - A.x, B.y - A.y);

		double v2_x = det2x2(p.y - B.y, p.z - B.z, C.y - B.y, C.z - B.z);
		double v2_y = -det2x2(p.x - B.x, p.z - B.z, C.x - B.x, C.z - B.z);
		double v2_z = det2x2(p.x - B.x, p.y - B.y, C.x - B.x, C.y - B.y);

		double v3_x = det2x2(p.y - C.y, p.z - C.z, C.y - B.y, C.z - B.z);
		double v3_y = -det2x2(p.x - C.x, p.z - C.z, C.x - B.x, C.z - B.z);
		double v3_z = det2x2(p.x - C.x, p.y - C.y, C.x - B.x, C.y - B.y);

		if (((v1_x * v2_x + v1_y * v2_y + v1_z * v2_z) > 0) && ((v1_x * v3_x + v1_y * v3_y + v1_z * v3_z) > 0))
			return true;

		return false;
	}

	//intersection on plane
	bool Triangle::inter_2D(const Triangle& that) const
	{
		//point inside triangle
		if (point_inside(that.A) || point_inside(that.B) || point_inside(that.C))
			return true;
		if (that.point_inside(A) || that.point_inside(B) || that.point_inside(C))
			return true;

		//intersect of line segments
		return inter_line_segs(that);
	}

	//initialization of line on 2 triangles(their planes)
	void Line::init(const Triangle& tr1, const Triangle& tr2)
	{
		ax = det2x2(tr1.b, tr1.c, tr2.b, tr2.c);
		ay = - det2x2(tr1.a, tr1.c, tr2.a, tr2.c);
		az = det2x2(tr1.a, tr1.b, tr2.a, tr2.b);
		//find point on a line

		if (fabs(ax) > EPSILON)
		{
			x0 = 0;
			if (fabs(tr1.b) > EPSILON)
			{
				z0 = det2x2(tr1.d, tr1.b, tr2.d, tr2.b) / ax;
				y0 = -(tr1.d - tr1.c * z0) / tr1.b;
			}
			else
			{
				y0 = det2x2(tr1.c, tr1.d, tr2.c, tr2.d) / ax;
				z0 = -(tr1.d - tr1.b * y0) / tr1.c;
			}
		}
		else if (fabs(ay) > EPSILON)
		{
			y0 = 0;
			if (fabs(tr1.a) > EPSILON)
			{
				z0 = det2x2(tr1.d, tr1.a, tr2.d, tr2.a) / ay;
				x0 = -(tr1.d - tr1.c * z0) / tr1.a;
			}
			else
			{
				x0 = det2x2(tr1.c, tr1.d, tr2.c, tr2.d) / ay;
				z0 = -(tr1.d - tr1.a * x0) / tr1.c;
			}
		}
		else if (fabs(az) > EPSILON)
		{
			z0 = 0;
			if (fabs(tr1.c) > EPSILON)
			{
				x0 = det2x2(tr1.d, tr1.b, tr2.d, tr2.b) / az;
				y0 = -(tr1.d - tr1.c * x0) / tr1.b;
			}
			else
			{
				y0 = det2x2(tr1.a, tr1.d, tr2.a, tr2.d) / az;
				x0 = -(tr1.d - tr1.b * y0) / tr1.a;
			}
		}
	}

	//get params of line
	double Line::get_ax() const { return ax; }
	double Line::get_ay() const { return ay; }
	double Line::get_az() const { return az; }
	double Line::get_x0() const { return x0; }
	double Line::get_y0() const { return y0; }
	double Line::get_z0() const { return z0; }

	//check intersections of 2 lines and return point 
	Triangle::Point* Line::line_inter(const Line& that)
	{
		double that_ax = that.get_ax();
		double that_ay = that.get_ay();
		double that_az = that.get_az();
		double that_x0 = that.get_x0();
		double that_y0 = that.get_y0();
		double that_z0 = that.get_z0();

		double det_xy = det2x2(ax, ay, that_ax, that_ay);
		double det_yz = det2x2(ay, az, that_ay, that_az);
		double det_xz = det2x2(ax, az, that_ax, that_az);

		//parallel lines
		if ((fabs(det_yz) <= EPSILON) && (fabs(det_xz) <= EPSILON) && (fabs(det_xy) <= EPSILON))
			return nullptr;

		double t;
		if (fabs(det_xy) > EPSILON)
		{
			double det1 = det2x2(that_x0, that_y0, that_ax, that_ay);
			double det2 = det2x2(x0, y0, that_ax, that_ay);
			t = (det1 - det2) / det_xy;
		}
		else if (fabs(det_xz) > EPSILON)
		{
			double det1 = det2x2(that_x0, that_z0, that_ax, that_az);
			double det2 = det2x2(x0, z0, that_ax, that_az);
			t = (det1 - det2) / det_xz;
		}
		else
		{
			double det1 = det2x2(that_y0, that_z0, that_ay, that_az);
			double det2 = det2x2(y0, z0, that_ay, that_az);
			t = (det1 - det2) / det_yz;
		}

		double x = x0 + t * ax;
		double y = y0 + t * ay;
		double z = z0 + t * az;

		Triangle::Point* point = new Triangle::Point{ x, y, z };
		return point;
	}

	bool Triangle::inter_line_segs(const Triangle& that) const
	{
		bool flag = false;
		Line AB = Line{ A, B };
		Line AC = Line{ A, C };
		Line BC = Line{ B, C };
		Triangle::Point* AB_AB = AB.line_inter(Line{ that.A, that.B });
		Triangle::Point* AB_AC = AB.line_inter(Line{ that.A, that.C });
		Triangle::Point* AB_BC = AB.line_inter(Line{ that.B, that.C });
		Triangle::Point* AC_AB = AC.line_inter(Line{ that.A, that.B });
		Triangle::Point* AC_AC = AC.line_inter(Line{ that.A, that.C });
		Triangle::Point* AC_BC = AC.line_inter(Line{ that.B, that.C });
		Triangle::Point* BC_AB = BC.line_inter(Line{ that.A, that.B });
		Triangle::Point* BC_AC = BC.line_inter(Line{ that.A, that.C });
		Triangle::Point* BC_BC = BC.line_inter(Line{ that.B, that.C });
		if ((AB_AB->between(A, B)) && (AB_AB->between(that.A, that.B)))
			flag = true;
		if ((AB_AC->between(A, B)) && (AB_AC->between(that.A, that.C)))
			flag = true;
		if ((AB_BC->between(A, B)) && (AB_BC->between(that.B, that.C)))
			flag = true;
		if ((AC_AB->between(A, C)) && (AC_AB->between(that.A, that.B)))
			flag = true;
		if ((AC_AC->between(A, C)) && (AC_AC->between(that.A, that.C)))
			flag = true;
		if ((AC_BC->between(A, C)) && (AC_BC->between(that.B, that.C)))
			flag = true;
		if ((BC_AB->between(B, C)) && (BC_AB->between(that.A, that.B)))
			flag = true;
		if ((BC_AC->between(B, C)) && (BC_AC->between(that.A, that.C)))
			flag = true;
		if ((BC_BC->between(B, C)) && (BC_BC->between(that.B, that.C)))
			flag = true;
		delete AB_AB, AB_AC, AB_BC, AC_AB, AC_AC, AC_BC, BC_AB, BC_AC, BC_BC;
		return flag;
	}

	void Triangle::print_trian() const
	{
		std::cout << "id: " << id << std::endl;
		std::cout << "A: " << A.x << " " << A.y << " " << A.z << std::endl;
		std::cout << "B: " << B.x << " " << B.y << " " << B.z << std::endl;
		std::cout << "C: " << C.x << " " << C.y << " " << C.z << std::endl;
	}
}
