#pragma once

#include "point3.hh"

class Light
{
public:
    virtual ~Light() = default;
    virtual double getIntensity() const = 0;
    virtual Point3 getPosition() const = 0;
    virtual void setIntensity(const double &intensity) = 0;
    virtual void setPosition(const Point3 &position) = 0;
    Light(double intensity) : intensity(intensity) {};

protected:
    double intensity;
};

class PointLight : public Light
{
public:
    PointLight() : Light(0), position(Point3()) {}
    PointLight(const Point3 &position, const double &intensity) : Light(intensity), position(position) {}

    Point3 getPosition() const { return position; }
    double getIntensity() const override { return intensity; }

    void setPosition(const Point3 &position) { this->position = position; }
    void setIntensity(const double &intensity) override { this->intensity = intensity; }

private:
    Point3 position;
};