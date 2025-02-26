#ifndef COLOR3_HH
#define COLOR3_HH

#include "vector3.hh"

class Color3 : public Vector3
{

public:
    Color3() : Vector3() {}
    Color3(const Vector3 &v) : Vector3(v) {}
    Color3(double u, double v, double w) : Vector3(u, v, w) {}
    Color3(const Color3 &other) = default;

    static Color3 from_rgb(double r, double g, double b)
    {
        return Color3(r / 255., g / 255., b / 255.);
    }

    int r() const { return (int)(255.999 * x); }
    int g() const { return (int)(255.999 * y); }
    int b() const { return (int)(255.999 * z); }

    Color3 clamp() const
    {
        return Color3(
            x > 1. ? 1. : x < 0. ? 0.
                                 : x,
            y > 1. ? 1. : y < 0. ? 0.
                                 : y,
            z > 1. ? 1. : z < 0. ? 0.
                                 : z);
    }

    Color3 blend(const Color3 &other) const
    {
        return Color3(
            x * other.x,
            y * other.y,
            z * other.z);
    }

    Color3 darken(double factor) const
    {
        return Color3(
            x * factor,
            y * factor,
            z * factor);
    }

    friend std::ostream &operator<<(std::ostream &out, const Color3 &c)
    {
        out << "{" << c.r() << ", " << c.g() << ", " << c.b() << "}";
        return out;
    }

    const static Color3 VOID;
};

const Color3 Color3::VOID = Color3(0, 0, 0);

#endif