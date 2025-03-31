#pragma once

#include "color3.hh"
#include "point3.hh"

class Ray;
class Hit;

class Object
{
public:
    virtual ~Object() = default;

    virtual bool intersect(const Ray &ray, Hit &hit) = 0;
    virtual Vector3 normal(const Point3 &point) const = 0;
    virtual Color3 getColor() const = 0;
    virtual double getKd() const = 0;
    virtual double getKs() const = 0;
    virtual double getNs() const = 0;

protected:
    Object(const Color3 &c, double diffuse_coeff, double speculative_coeff, double ns)
        : color(c), kd(diffuse_coeff), ks(speculative_coeff), ns(ns) {}

    const Color3 color;
    const double kd;
    const double ks;
    const double ns;
};

class Sphere : public Object
{
public:
    Sphere(const Point3 &center, double radius, const Color3 &color)
        : Object(color, 0.8, 0.8, 128), center(center), radius(radius)
    {
    }

    Sphere(const Point3 &center, double radius)
        : Object(Color3(1, 1, 1), 0.8, 0.8, 128), center(center), radius(radius)
    {
    }

    Color3 getColor() const
    {
        return color;
    }

    double getKd() const
    {
        return kd;
    }

    double getKs() const {
        return ks;
    }

    double getNs() const {
        return ns;
    }

    void setCenter(const Point3 &center)
    {
        this->center = center;
    }

    void setRadius(double radius)
    {
        this->radius = radius;
    }

    bool intersect(const Ray &ray, Hit &hit) override;

    Vector3 normal(const Point3 &point) const override
    {
        return (point - center) / radius;
    }

private:
    Point3 center;
    double radius;
};