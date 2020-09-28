#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

const double EPSILON = 0.001;

struct Point {
    double x;
    double y;
};

struct Line_seg {
    Point p1;
    Point p2;
    Line_seg(const Point& first, const Point& second) :
        p1{ first },
        p2{ second }
    {}
};

struct Line {
    double a;
    double b;
    double c;
    void init(Line_seg& ls)
    {
        if (fabs(ls.p2.x - ls.p1.x) < EPSILON)
        {
            b = 0;
            a = 1;
            c = -ls.p1.x;
        }
        else if (fabs(ls.p2.y - ls.p1.y) < EPSILON)
        {
            a = 0;
            b = 1;
            c = -ls.p1.y;
        }
        else
        {
            a = 1;
            b = (ls.p1.x - ls.p2.x) / (ls.p2.y - ls.p1.y);
            c = -ls.p1.x - b * ls.p1.y;
        }
    }
};

struct Triangle {
    Point A = { 0, 0 };
    Point B = { 0, 0 };
    Point C = { 0, 0 };
    Line_seg AB = { A, B };
    Line_seg BC = { B, C };
    Line_seg AC = { A, C };

    void init_segs()
    {
        AB = { A, B };
        BC = { B, C };
        AC = { A, C };
    }
    bool contains_point(Point& point)
    {
        double value1 = (A.x - point.x) * (B.y - A.y) - (B.x - A.x) * (A.y - point.y);
        double value2 = (B.x - point.x) * (C.y - B.y) - (C.x - B.x) * (B.y - point.y);
        double value3 = (C.x - point.x) * (A.y - C.y) - (A.x - C.x) * (C.y - point.y);
        if ((value1 < EPSILON) && (value2 < EPSILON) && (value3 < EPSILON))
            return true;
        if ((value1 > -EPSILON) && (value2 > -EPSILON) && (value3 > -EPSILON))
            return true;
        return false;
    }
};

double max(double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}

double min(double a, double b)
{
    if (a < b)
        return a;
    else
        return b;
}

bool intersect_ls(Line_seg& ls1, Line_seg& ls2)
{
    double Ax = ls1.p1.x;
    double Bx = ls1.p2.x;
    double Cx = ls2.p1.x;
    double Dx = ls2.p2.x;
    double Ay = ls1.p1.y;
    double By = ls1.p2.y;
    double Cy = ls2.p1.y;
    double Dy = ls2.p2.y;

    Line line1, line2;
    line1.init(ls1);
    line2.init(ls2);
    double det = line1.a * line2.b - line1.b * line2.a;
    if (fabs(det) < EPSILON)
    {
        double c1_mod;
        double c2_mod;
        if (fabs(line1.a) > EPSILON)
        {
            c1_mod = line1.c / line1.a;
            c2_mod = line2.c / line2.a;
        }
        else
        {
            c1_mod = line1.c / line1.b;
            c2_mod = line2.c / line2.b;
        }

        if (fabs(c1_mod - c2_mod) < EPSILON)  //on one line
        {
            if ((Cx < max(Ax, Bx) + EPSILON) && (Cx > min(Ax, Bx) - EPSILON))
                return true;
            else if ((Dx < max(Ax, Bx) + EPSILON) && (Dx > min(Ax, Bx) - EPSILON))
                return true;
            else if ((Ax < max(Cx, Dx) + EPSILON) && (Ax > min(Cx, Dx) - EPSILON))
                return true;
            else if ((Bx < max(Cx, Dx) + EPSILON) && (Bx > min(Cx, Dx) - EPSILON))
                return true;
            else
                return false;
        }
        else //parallel
            return false;
    }
    else //lines intersect
    {
        double y_int = (line2.a * line1.c - line2.c * line1.a) / det;
        double x_int = (line2.c * line1.b - line2.b * line1.c) / det;
        if ((x_int < max(Ax, Bx) + EPSILON) && (x_int < max(Cx, Dx) + EPSILON) &&
            (x_int > min(Ax, Bx) - EPSILON) && (x_int > min(Cx, Dx) - EPSILON) &&
            (y_int < max(Ay, By) + EPSILON) && (y_int < max(Cy, Dy) + EPSILON) &&
            (y_int > min(Ay, By) - EPSILON) && (y_int > min(Cy, Dy) - EPSILON))
            return true;
        else
            return false;
    }
}

bool intersect_tr(Triangle& tr1, Triangle& tr2)
{
    if (tr1.contains_point(tr2.A) || tr1.contains_point(tr2.B) || tr1.contains_point(tr2.C))
        return true;
    if (tr2.contains_point(tr1.A) || tr2.contains_point(tr1.B) || tr2.contains_point(tr1.C))
        return true;
    if (intersect_ls(tr1.AB, tr2.AB) || intersect_ls(tr1.AB, tr2.BC) || intersect_ls(tr1.AB, tr2.AC))
        return true;
    if (intersect_ls(tr1.BC, tr2.AB) || intersect_ls(tr1.BC, tr2.BC) || intersect_ls(tr1.BC, tr2.AC))
        return true;
    if (intersect_ls(tr1.AC, tr2.AB) || intersect_ls(tr1.AC, tr2.BC) || intersect_ls(tr1.AC, tr2.AC))
        return true;
    return false;

}
