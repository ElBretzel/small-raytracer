#ifndef POINT3_HH
#define POINT3_HH

#include "vector3.hh"

// Mostly like Vector3, but with a few more operators
// This is used to separate concepts between Vector and Point (mathematically speaking)

class Point3 : public Vector3
{
public:
    Point3() : Vector3() {}
    Point3(double x, double y, double z) : Vector3(x, y, z) {}

    friend std::ostream &operator<<(std::ostream &out, const Point3 &p)
    {
        out << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
        return out;
    }

    Point3 operator+(const Vector3 &v) const
    {
        return Point3(getX() + v.getX(), getY() + v.getY(), getZ() + v.getZ());
    }

    Point3 operator-(const Vector3 &v) const
    {
        return Point3(getX() - v.getX(), getY() - v.getY(), getZ() - v.getZ());
    }

    Point3 operator*(double t) const
    {
        return Point3(getX() * t, getY() * t, getZ() * t);
    }

    Point3 operator/(double t) const
    {
        return Point3(getX() / t, getY() / t, getZ() / t);
    }

    inline double distance(const Point3 &other) const
    {
        return std::sqrt(std::pow(getX() - other.getX(), 2) + std::pow(getY() - other.getY(), 2) + std::pow(getZ() - other.getZ(), 2));
    }

    const static Point3 ORIGIN;
};

// Some utility functions for Point3
// Those methods are inlined
namespace point3
{
    inline double distance(const Point3& p1, const Point3& p2) {
        return std::sqrt(std::pow(p1.getX() - p2.getX(), 2) + std::pow(p1.getY() - p2.getY(), 2) + std::pow(p1.getZ() - p2.getZ(), 2));
    }

    inline Vector3 construct_vect(const Point3& from, const Point3& to) {
        return Vector3(to.getX() - from.getX(), to.getY() - from.getY(), to.getZ() - from.getZ());
    }
}

const Point3 Point3::ORIGIN = Point3(0, 0, 0);

#endif