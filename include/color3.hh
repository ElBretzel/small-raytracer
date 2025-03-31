#pragma once

#include <iostream>

class Color3
{

public:
    constexpr Color3() : u(0), v(0), w(0) {}
    constexpr Color3(double u, double v, double w) : u(u), v(v), w(w) {}
    constexpr Color3(const Color3 &other) : u(other.u), v(other.v), w(other.w) {}

    static Color3 from_rgb(double r, double g, double b)
    {
        return Color3(r / 255., g / 255., b / 255.);
    }

    int r() const { return (int)(255.999 * u); }
    int g() const { return (int)(255.999 * v); }
    int b() const { return (int)(255.999 * w); }

    inline Color3 clamp() const
    {
        return Color3(
            u > 1. ? 1. : u < 0. ? 0.
                                 : u,
            v > 1. ? 1. : v < 0. ? 0.
                                 : v,
            w > 1. ? 1. : w < 0. ? 0.
                                 : w);
    }

    Color3 operator+(const Color3 &other) const
    {
        return Color3(
            u + other.u,
            v + other.v,
            w + other.w);
    }

    Color3& operator+=(const Color3 &other)
    {
        u += other.u;
        v += other.v;
        w += other.w;
        return *this;
    }

    Color3 operator-(const Color3 &other) const
    {
        return Color3(
            u - other.u,
            v - other.v,
            w - other.w);
    }

    Color3 operator*(double factor) const
    {
        return Color3(
            u * factor,
            v * factor,
            w * factor);
    }

    friend std::ostream &operator<<(std::ostream &out, const Color3 &c)
    {
        out << "{" << c.r() << ", " << c.g() << ", " << c.b() << "}";
        return out;
    }



    static const Color3 VOID;
    static const Color3 AETHER;

private:
    double u;
    double v;
    double w;
};

constexpr Color3 Color3::VOID = Color3(0, 0, 0);
constexpr Color3 Color3::AETHER = Color3(1, 1, 1);