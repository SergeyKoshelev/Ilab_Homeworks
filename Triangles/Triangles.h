#pragma once

#include <iostream>
#include <cmath>

const double EPSILON = 0.00000001;


namespace Triangles {

	class Line;

	class Triangle {
	public:
		class Point {
		public:
			double x, y, z;

			Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};
			Point(Point* p) : x(p->x), y(p->y), z(p->z) {};

			bool operator == (const Point& that) const;

			bool between(const Point& p1, const Point& p2) const;
			bool between(Point* p1, Point* p2) const;
			bool on_line(const Point& p1, const Point& p2) const;
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
		bool two_line_segs(const Point& p11, const Point& p12, const Point& p21, const Point& p22) const;

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
		Triangle::Point* line_inter(const Line& that) const;
		double get_ax() const;
		double get_ay() const;
		double get_az() const;
		double get_x0() const;
		double get_y0() const;
		double get_z0() const;
		bool inter_on_common_line(const Triangle& t1, const Triangle& tr2) const;
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
				if (std::fabs(z - that.z) <= EPSILON)
					return true;

		return false;
	}

	//check if point is between 2 other points (condition is that there are on 1 line)
	bool Triangle::Point::between(const Point& p1, const Point& p2) const
	{
		if ((x < (std::max(p1.x, p2.x) + EPSILON)) && (x > (std::min(p1.x, p2.x) - EPSILON)) &&
			(y < (std::max(p1.y, p2.y) + EPSILON)) && (y > (std::min(p1.y, p2.y) - EPSILON)) &&
			(z < (std::max(p1.z, p2.z) + EPSILON)) && (z > (std::min(p1.z, p2.z) - EPSILON)))
			return true;
		return false;
	}

	////check if point is between 2 other points (condition is that there are on 1 line) (overrided for pointers)
	bool Triangle::Point::between(Point* p1, Point* p2) const
	{
		if ((p1 == nullptr) || (p2 == nullptr))
			return false;
		else if ((x < (std::max(p1->x, p2->x) + EPSILON)) && (x > (std::min(p1->x, p2->x) - EPSILON)) &&
			(y < (std::max(p1->y, p2->y) + EPSILON)) && (y > (std::min(p1->y, p2->y) - EPSILON)) &&
			(z < (std::max(p1->z, p2->z) + EPSILON)) && (z > (std::min(p1->z, p2->z) - EPSILON)))
			return true;
		else return false;
	}

	//check if points are on 1 line
	bool Triangle::Point::on_line(const Point& p1, const Point& p2) const
	{
		double t = 0;
		Line line = Line{ p1, p2 };
		if (fabs(line.get_ax()) > EPSILON)
			t = (x - line.get_x0()) / line.get_ax();
		else if (fabs(line.get_ay()) > EPSILON)
			t = (y - line.get_y0()) / line.get_ay();
		else 
			t = (z - line.get_z0()) / line.get_az();
		double new_x = line.get_x0() + line.get_ax() * t;
		double new_y = line.get_y0() + line.get_ay() * t;
		double new_z = line.get_z0() + line.get_az() * t;

		if ((fabs(new_x - x) < EPSILON) && (fabs(new_y - y) < EPSILON) && (fabs(new_z - z) < EPSILON))
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
		if (A.on_line(B, C))
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

		if ((res1 < -EPSILON) && (res2 < -EPSILON) && (res3 < -EPSILON))
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
		Triangle this_tr = Triangle{ id, Point{A.x, A.y, A.z}, Point{B.x, B.y, B.z}, Point{C.x, C.y, C.z} };
		Line common_line = Line{ that, this_tr};

		return common_line.inter_on_common_line(that, this_tr);
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
		double len_v1 = v1_x * v1_x + v1_y * v1_y + v1_z * v1_z;

		double v2_x = det2x2(p.y - B.y, p.z - B.z, C.y - B.y, C.z - B.z);
		double v2_y = -det2x2(p.x - B.x, p.z - B.z, C.x - B.x, C.z - B.z);
		double v2_z = det2x2(p.x - B.x, p.y - B.y, C.x - B.x, C.y - B.y);
		double len_v2 = v2_x * v2_x + v2_y * v2_y + v2_z * v2_z;

		double v3_x = det2x2(p.y - C.y, p.z - C.z, C.y - B.y, A.z - C.z);
		double v3_y = -det2x2(p.x - C.x, p.z - C.z, C.x - B.x, A.z - C.z);
		double v3_z = det2x2(p.x - C.x, p.y - C.y, C.x - B.x, A.y - C.y);
		double len_v3 = v3_x * v3_x + v3_y * v3_y + v3_z * v3_z;

		double sqal_v1_v2 = v1_x * v2_x + v1_y * v2_y + v1_z * v2_z;
		double sqal_v1_v3 = v1_x * v3_x + v1_y * v3_y + v1_z * v3_z;

		if ((sqal_v1_v2 > EPSILON) && (sqal_v1_v3 > EPSILON))
			return true;

		if ((len_v1 == 0) && (p.between(A, B)))
			return true;
		if ((len_v2 == 0) && (p.between(B, C)))
			return true;
		if ((len_v3 == 0) && (p.between(C, A)))
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
	Triangle::Point* Line::line_inter(const Line& that) const 
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

	//check intersections of triangles' line segments
	bool Triangle::inter_line_segs(const Triangle& that) const
	{
		bool flag = two_line_segs(A, B, that.A, that.B) || two_line_segs(A, B, that.A, that.C) || two_line_segs(A, B, that.B, that.C) ||
			two_line_segs(A, C, that.A, that.B) || two_line_segs(A, C, that.A, that.C) || two_line_segs(A, C, that.B, that.C) ||
			two_line_segs(B, C, that.A, that.B) || two_line_segs(B, C, that.A, that.C) || two_line_segs(B, C, that.B, that.C);
		return flag;
	}

	//check intersect of 2 line segs on points
	bool Triangle::two_line_segs(const Point& p11, const Point& p12, const Point& p21, const Point& p22) const
	{
		bool flag = false;
		Line line1 = Line{ p11, p12 };
		Line line2 = Line{ p21, p22 };
		Triangle::Point* inter_point = line1.line_inter(line2);
		if (inter_point && (inter_point->between(p11, p12)) && (inter_point->between(p21, p22)))
			flag = true;
		delete inter_point;
		return flag;
	}

	//print triangle
	void Triangle::print_trian() const
	{
		std::cout << "id: " << id << std::endl;
		std::cout << "A: " << A.x << " " << A.y << " " << A.z << std::endl;
		std::cout << "B: " << B.x << " " << B.y << " " << B.z << std::endl;
		std::cout << "C: " << C.x << " " << C.y << " " << C.z << std::endl;
	}

	//check intersection of triangles on common line
	bool Line::inter_on_common_line(const Triangle& tr1, const Triangle& tr2) const
	{
		bool flag = false;
		Triangle::Point* with_AB1 = line_inter(Line{ tr1.A, tr1.B });
		Triangle::Point* with_AC1 = line_inter(Line{ tr1.A, tr1.C });
		Triangle::Point* with_BC1 = line_inter(Line{ tr1.B, tr1.C });
		Triangle::Point* with_AB2 = line_inter(Line{ tr2.A, tr2.B });
		Triangle::Point* with_AC2 = line_inter(Line{ tr2.A, tr2.C });
		Triangle::Point* with_BC2 = line_inter(Line{ tr2.B, tr2.C });

		Triangle::Point* p11 = nullptr;
		Triangle::Point* p12 = nullptr;
		Triangle::Point* p21 = nullptr;
		Triangle::Point* p22 = nullptr;

		if (with_AB1 && with_AC1 && with_AB1->between(tr1.A, tr1.B) && with_AC1->between(tr1.A, tr1.C))
		{
			p11 = with_AB1;
			p12 = with_AC1;
		}
		else if (with_AB1 && with_BC1 && with_AB1->between(tr1.A, tr1.B) && with_BC1->between(tr1.B, tr1.C))
		{
			p11 = with_AB1;
			p12 = with_BC1;
		}
		else if (with_BC1 && with_AC1 && with_BC1->between(tr1.B, tr1.C) && with_AC1->between(tr1.A, tr1.C))
		{
			p11 = with_BC1;
			p12 = with_AC1;
		}

		if (with_AB2 && with_AC2 && with_AB2->between(tr2.A, tr2.B) && with_AC2->between(tr2.A, tr2.C))
		{
			p21 = with_AB2;
			p22 = with_AC2;
		}
		else if (with_AB2 && with_BC2 && with_AB2->between(tr2.A, tr2.B) && with_BC2->between(tr2.B, tr2.C))
		{
			p21 = with_AB2;
			p22 = with_BC2;
		}
		else if (with_BC2 && with_AC2 && with_BC2->between(tr2.B, tr2.C) && with_AC2->between(tr2.A, tr2.C))
		{
			p21 = with_BC2;
			p22 = with_AC2;
		}

		if ((p11 && p11->between(p21, p22)) || 
			(p12 && p12->between(p21, p22)) || 
			(p21 && p21->between(p11, p12)) || 
			(p22 && p22->between(p11, p12)))
			flag = true;
		delete with_AB1, with_AC1, with_BC1, with_AB2, with_AC2, with_BC2;
		return flag;
	}
}
