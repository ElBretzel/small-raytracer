// This file is used to break circular deps (not thanks to chatgpt...)
// cpp kinda trash

#ifndef RAY_IMPL_HH
#define RAY_IMPL_HH


#include "light.hh"
#include "object.hh"
#include "ray.hh"
#include "point3.hh"
inline Color3 Ray::cast(const std::vector<std::shared_ptr<Object>> &objects, const std::vector<std::shared_ptr<Light>> &lights) const
{
    Hit buff;
    Hit best_hit;
    std::shared_ptr<Object> closest = nullptr;
    double closest_dist = INFINITY;
    for (auto &object : objects)
    {
        if (object->intersect(*this, buff))
        {
            double curr_dist = distance(this->origin, buff.point);
            if (curr_dist < closest_dist) {
                closest = object;
                closest_dist = curr_dist;
                best_hit = buff;
            }
        }
    }
    // No Hit
    if (closest == nullptr)
        return Color3();

    Color3 accumulator = Color3::VOID;
    for (auto &light : lights) {
        auto light_vect = vect_from_points(best_hit.point, light->getPosition());
        std::cout << closest->getColor().darken(closest->kd * best_hit.normal.dot(light_vect) * light->getIntensity()) << std::endl;
        accumulator = accumulator.blend(closest->getColor().darken(closest->kd * best_hit.normal.dot(light_vect) * light->getIntensity()));
    }
    return accumulator;
}

#endif