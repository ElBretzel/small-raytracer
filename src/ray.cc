#include "ray.hh"

#include <bits/stl_algo.h>

#include "light.hh"
#include "object.hh"

Color3 Ray::cast(const std::vector<std::shared_ptr<Object>> &objects, const std::vector<std::shared_ptr<Light>> &lights, int max_iteration, int current_iteration, int current_index) const
{
    Hit buff;
    Hit best_hit;
    std::shared_ptr<Object> closest = nullptr;
    int best_hit_index = -1;
    double closest_dist = INFINITY;
    for (auto &object : objects)
    {
        // Check if current object from hit is cast
        if (current_index >= 0 && objects[current_index] == object)
            continue;
        if (object->intersect(*this, buff))
        {
            double curr_dist = point3::distance(this->origin, buff.point);
            if (curr_dist < closest_dist)
            {
                closest = object;
                closest_dist = curr_dist;
                best_hit = buff;
                best_hit_index = &object - &objects[0];
            }
        }
    }
    // No Hit
    if (closest == nullptr)
        return Color3();

    Color3 accumulator = Color3::VOID;
    for (const auto &light : lights)
    {
        auto light_vect = point3::construct_vect(best_hit.point, light->getPosition()).normalize();
        accumulator += closest->getColor() * closest->getKd() * best_hit.normal.normalize().dot(light_vect) * light->getIntensity();
        auto normal = best_hit.normal.normalize();
        auto S = this->getDirection().normalize() - normal * 2 * this->getDirection().normalize().dot(normal);
        S = S.normalize();
        if (light_vect.dot(normal) > 0.0) {
            accumulator += Color3::AETHER *
                        closest->getKs() *
                        light->getIntensity() *
                        pow(
                            std::clamp(S.dot(light_vect), 0., 1.),
                            closest->getNs()
                            );

        }

        accumulator = accumulator.clamp();
    }
    if (max_iteration == current_iteration)
        return accumulator;
    else {
        accumulator += Ray(best_hit.point, best_hit.normal).cast(objects,lights,max_iteration, current_iteration+1, best_hit_index) * closest->getKs();
        return accumulator.clamp();
    }
}
