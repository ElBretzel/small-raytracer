#include "hit.hh"
#include "object.hh"
#include "ray.hh"

bool Sphere::intersect(const Ray &ray, Hit &hit)
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

    double root1 = (-b - sqrtd) / (2 * a);
    double root2 = (-b + sqrtd) / (2 * a);

    Point3 root_point1 = ray.at(root1);
    Point3 root_point2 = ray.at(root2);
    double distance1 = point3::distance(ray.getOrigin(), root_point1);
    double distance2 = point3::distance(ray.getOrigin(), root_point2);
    Point3 closest_hit = distance1 < distance2 ? root_point1 : root_point2; // Choose the closest root point

    hit.point = closest_hit;
    hit.normal = normal(hit.point);

    return true;
}