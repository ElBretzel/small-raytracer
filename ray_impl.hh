// This file is used to break circular deps (not thanks to chatgpt...)
// cpp kinda trash

#ifndef RAY_IMPL_HH
#define RAY_IMPL_HH

#include "light.hh"
#include "object.hh"
#include "ray.hh"

inline Color3 Ray::cast(const std::vector<std::shared_ptr<Object>> &objects, const std::vector<std::shared_ptr<Light>> &lights) const
{
    Hit hit;
    for (const auto &object : objects)
    {
        if (object->intersect(*this, hit))
        {
            return object->getColor();
        }
    }
    return Color3(0, 0, 0);
}

#endif