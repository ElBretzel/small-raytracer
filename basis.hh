#ifndef BASIS_HH
#define BASIS_HH

#include "vector3.hh"
#include "point3.hh"

// Util class to represent a basis in 3D space
// Very useful for camera and raytracing (+ storing the origin)
class Basis
{
    public:
        Basis () : x(Vector3(1, 0, 0)), y(Vector3(0, 1, 0)), z(Vector3(0, 0, 1)), origin(Point3(0, 0, 0)) {}
        Basis (const Vector3 &x, const Vector3 &y, const Vector3 &z) : x(x), y(y), z(z), origin(Point3(0, 0, 0)) {}
        Basis (const Vector3 &x, const Vector3 &y, const Vector3 &z, const Point3 &origin) : x(x), y(y), z(z), origin(origin) {}
        Basis (const Basis &other, const Point3 &origin) : x(other.x), y(other.y), z(other.z), origin(origin) {}

        inline static Basis fromZ(const Vector3 &z, const Vector3 &other)
        {
            Vector3 x = other.cross(z).normalize();
            Vector3 y = z.cross(x).normalize();
            return Basis(x, y, z);
        }

        inline static Basis fromY(const Vector3 &y, const Vector3 &other)
        {
            Vector3 x = other.cross(y).normalize();
            Vector3 z = y.cross(x).normalize();
            return Basis(x, y, z);
        }

        inline static Basis fromX(const Vector3 &x, const Vector3 &other)
        {
            Vector3 y = other.cross(x).normalize();
            Vector3 z = x.cross(y).normalize();
            return Basis(x, y, z);
        }

        Vector3 getX() const { return x; }
        Vector3 getY() const { return y; }
        Vector3 getZ() const { return z; }
        Point3 getOrigin() const { return origin; }

        friend std::ostream &operator<<(std::ostream &out, const Basis &b)
        {
            out << "Basis(" << b.x << ", " << b.y << ", " << b.z << ", " << b.origin << ")";
            return out;
        }

    private:
        const Vector3 x;
        const Vector3 y;
        const Vector3 z;
        const Point3 origin;
};

#endif