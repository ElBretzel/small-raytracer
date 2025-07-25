#ifndef RAY_HH
#define RAY_HH

#include "point3.hh"
#include "vector3.hh"
#include "color3.hh"
#include "hit.hh"

#include <vector>
#include <memory>

class Object;
class Light;

class Ray
{
public:
    Ray() : origin(Point3()), direction(Vector3()) {}
    Ray(const Point3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}

    Point3 getOrigin() const { return origin; }
    Vector3 getDirection() const { return direction; }

    Point3 at(double t) const
    {
        return origin + direction * t;
    }

    Color3 cast(const std::vector<std::shared_ptr<Object>> &objects, const std::vector<std::shared_ptr<Light>> &lights) const;

    friend std::ostream &operator<<(std::ostream &out, const Ray &r)
    {
        out << "Ray(" << r.origin << ", " << r.direction << ")";
        return out;
    }

    constexpr static double MIN = 0.01;
    constexpr static double MAX = 1000.0;

private:
    const Point3 origin;
    const Vector3 direction;
};

#endif