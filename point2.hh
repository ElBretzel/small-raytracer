#ifndef POINT2_HH
#define POINT2_HH

#include <iostream>

class Point2
{
public:
    Point2() : x(0), y(0) {}
    Point2(double x, double y) : x(x), y(y) {}
    Point2(const Point2 &other) = default;

    double getX() const { return x; }
    double getY() const { return y; }

    friend std::ostream &operator<<(std::ostream &out, const Point2 &p)
    {
        out << "Point2(" << p.x << ", " << p.y << ")";
        return out;
    }

protected:
    double x, y;
};

#endif