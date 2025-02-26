#ifndef LIGHT_HH
#define LIGHT_HH

#include "color3.hh"
#include "point3.hh"

class Light
{
public:
    virtual ~Light() = default;
    virtual Color3 getIntensity() const = 0;
    virtual void setIntensity(const Color3 &intensity) = 0;

protected:
    Color3 intensity;
};

class PointLight : public Light
{
public:
    PointLight() : position(Point3()), intensity(Color3()) {}
    PointLight(const Point3 &position, const Color3 &intensity) : position(position), intensity(intensity) {}

    Point3 getPosition() const { return position; }
    Color3 getIntensity() const override { return intensity; }

    void setPosition(const Point3 &position) { this->position = position; }
    void setIntensity(const Color3 &intensity) override { this->intensity = intensity; }

private:
    Point3 position;
    Color3 intensity;
};

#endif