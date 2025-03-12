#pragma once

#include "color3.hh"
#include "point2.hh"

#include <memory>

class Pixel
{
public:
    Pixel() : color(std::make_unique<Color3>(Color3::VOID)), position(Point2()) {}
    Pixel(const Point2 &position) : color(std::make_unique<Color3>(Color3::VOID)), position(position) {}
    Pixel(const Color3 &color, const Point2 &position) : color(std::make_unique<Color3>(color)), position(position) {}

    Pixel(const Pixel &other) = delete;

    Color3 getColor() const { return *color; }
    Point2 getPosition() const { return position; }
    void setColor(const Color3 &color)
    {
        this->color = std::make_unique<Color3>(color);
    }

    friend std::ostream &operator<<(std::ostream &out, const Pixel &p)
    {
        out << "Pixel(" << *p.color << ", " << p.position << ", " << ")";
        return out;
    }

private:
    // This solution is not ideal but copy constructor was a pain to use
    // Because I do not want to manage memory and dangling ref, I just used a unique_ptr
    std::unique_ptr<Color3> color;
    const Point2 position;
};