#pragma once

#include "pixel.hh"
#include <fstream>
#include <vector>

class Image
{
public:
    Image(int width, double aspectRatio);

    const std::vector<std::shared_ptr<Pixel>> getPixels() const { return pixels; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    double getAspectRatio() const { return aspectRatio; }

    void setPixel(const Point2 &position, const Color3 &color)
    {
        pixels[position.getY() * width + position.getX()].get()->setColor(color);
    }
    void setPixel(const Pixel &pixel)
    {
        pixels[pixel.getPosition().getY() * width + pixel.getPosition().getX()] = std::make_shared<Pixel>(pixel.getColor(), pixel.getPosition());
    }

    void create_debug_gradient();

    void save_to_ppm(const char *filename) const;

    friend std::ostream &operator<<(std::ostream &out, const Image &i)
    {
        out << "Image(" << i.width << ", " << i.height << ", " << i.aspectRatio << ")";
        return out;
    }

private:
    // vector of shared_ptr is a good idea to avoid copying the pixels (and handling memory)
    std::vector<std::shared_ptr<Pixel>> pixels;
    const int width, height;
    const double aspectRatio;
};