#pragma once

#include "basis.hh"
#include "image.hh"

constexpr double DEFAULT_ASPECT_RATIO = 16.0 / 9.0;
constexpr double DEFAULT_WIDTH = 800.0;

class Screen
{
public:
    Screen(const std::shared_ptr<Basis> &basis, int focal_length, double fov, std::unique_ptr<Image> image = nullptr);
    Screen(std::unique_ptr<Image> image, const std::shared_ptr<Basis> &basis, int focal_length, double fov) : Screen(basis, focal_length, fov, std::move(image)) {}

    Point3 getPixelPosition(int i, int j) const
    {
        // pixel_size have width and height from the image plane (we some kind of scanline)
        return _position + (cameraBasis->getX() * pixel_size * i) - (cameraBasis->getY() * pixel_size * j);
    }

    Basis getBasis() const { return *cameraBasis; }

    Point3 getPosition() const { return _position; }

    Image &getImage() const { return *image; }

    void setFov(double fov, double focal_length);

    friend std::ostream &operator<<(std::ostream &out, const Screen &s)
    {
        out << "Screen(" << s.cameraBasis << ", " << s._position << ", " << s.screen_width << ", " << s.screen_height << ", " << s.pixel_size << ")";
        return out;
    }

private:
    std::shared_ptr<Basis> cameraBasis;
    std::unique_ptr<Image> image;

    Point3 _position; // SHOULD NOT BE MODIFIED MANUALLY!!
    double screen_width;
    double screen_height;
    double pixel_size;
};