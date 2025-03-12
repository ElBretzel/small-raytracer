#ifndef OBJECT_HH
#define OBJECT_HH

#include "point3.hh"
#include "vector3.hh"
#include "color3.hh"
#include "hit.hh"
#include "ray.hh"

class Object
{
public:
    virtual ~Object() = default;

    virtual bool intersect(const Ray &ray, Hit& hit) = 0;
    virtual Vector3 normal(const Point3 &point) const = 0;

    virtual Color3 getColor() const = 0;
    const double kd;

protected:
    Object(const Color3& c, double diffuse_coeff)
    : color(c), kd(diffuse_coeff) {}
    Color3 color;
};

class Sphere : public Object
{
public:
    Sphere(const Point3 &center, double radius, const Color3 &color)
        : Object(color, 0.5), center(center), radius(radius)
    {
    }

    Sphere(const Point3 &center, double radius)
    : Object(Color3(1,1,1), 0.5), center(center), radius(radius)
    {
    }

    bool intersect(const Ray &ray, Hit& hit) override
    {
        // This can be found from the equation of a sphere at the point c + the equation of a ray p
        // (p - c) * (p - c) = r^2 (just solve and find the roots t)
        Vector3 oc = ray.getOrigin() - center;
        double a = ray.getDirection().lengthSquared();
        double b = 2 * oc.dot(ray.getDirection());
        double c = oc.lengthSquared() - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
        {
            return false;
        }

        double sqrtd = sqrt(discriminant);

        Point3 root1 = ray.at((b - sqrtd) / (2 * a));
        Point3 root2 = ray.at((-b + sqrtd) / (2 * a));
        // If both root are < 0, the object is behind the camera
        // If one root is == 0, the object is tangent to the camera
        // If two roots are > 0, the object is in front of the camera
        Point3 root = point3::distance(ray.getOrigin(), root1) < point3::distance(ray.getOrigin(), root2) ? root1 : root2;
        
        hit.point = root;
        hit.normal = normal(hit.point);

        return true;
    }

    Vector3 normal(const Point3 &point) const override
    {
        return (point - center) / radius;
    }

    Color3 getColor() const
    {
        return color;
    }

    void setColor(const Color3 &color)
    {
        this->color = color;
    }

    void setCenter(const Point3 &center)
    {
        this->center = center;
    }

    void setRadius(double radius)
    {
        this->radius = radius;
    }

private:
    Point3 center;
    double radius;
};

#endif