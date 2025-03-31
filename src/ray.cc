#include "ray.hh"
#include "light.hh"
#include "object.hh"

Color3 Ray::cast(const std::vector<std::shared_ptr<Object>> &objects, const std::vector<std::shared_ptr<Light>> &lights) const
{
    Hit buff;
    Hit best_hit;
    std::shared_ptr<Object> closest = nullptr;
    double closest_dist = INFINITY;
    for (auto &object : objects)
    {
        if (object->intersect(*this, buff))
        {
            double curr_dist = point3::distance(this->origin, buff.point);
            if (curr_dist < closest_dist)
            {
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
    for (const auto &light : lights)
    {
        auto light_vect = point3::construct_vect(best_hit.point, light->getPosition()).normalize();
        accumulator += closest->getColor() * closest->getKd() * best_hit.normal.normalize().dot(light_vect) * light->getIntensity();
        auto normal = best_hit.normal.normalize();
        auto S = light_vect - normal * 2 * light_vect.dot(normal);

        if (light_vect.dot(normal) > 0.0) {
            accumulator += Color3::AETHER *
                        closest->getKs() *
                        light->getIntensity() *
                        pow(
                            S.dot(light_vect),
                            closest->getNs()
                            );

        }


        accumulator = accumulator.clamp();


    }
    return accumulator;
}
