#ifndef IMAGE_HH
#define IMAGE_HH

#include "pixel.hh"
#include <fstream>
#include <vector>

class Image
{
public:
    Image(int width, double aspectRatio) : width(width), height((int)width / aspectRatio), aspectRatio(aspectRatio)
    {

        // Dummy pixel (so I can use the same index for the pixels)
        pixels.reserve(width * height);
        for (int i = 0; i < width * height; i++)
        {
            pixels.push_back(std::make_shared<Pixel>());
        }
    }

    const std::vector<std::shared_ptr<Pixel>> getPixels() const { return pixels; }

    void setPixel(const Point2& position, const Color3& color)
    {
        pixels[position.getY() * width + position.getX()].get()->setColor(color);
    }
    void setPixel(const Pixel& pixel)
    {
        pixels[pixel.getPosition().getY() * width + pixel.getPosition().getX()] = std::make_shared<Pixel>(pixel.getColor(), pixel.getPosition());
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    double getAspectRatio() const { return aspectRatio; }

    void create_debug_gradient()
    {
        for (int i = 0; i < width * height; i++)
        {
            Color3 r = Color3((double)(i % width) / (double)width, 0, 0);
            Color3 g = Color3(0, (double)(i / width) / (double)height, 0);
            Color3 b = Color3(0, 0, (double)i / (double)(width * height));
            Point2 position = Point2(i % width, i / width);
            Color3 final_color = r + g + b;
            setPixel(position, final_color);
        }
    }

    void save_to_ppm(const char *filename) const
    {
        std::ofstream file;
        file.open(filename);

        file << "P3" << " " << width << " " << height << " " << "255" << "\n";

        for (const auto &pixel : pixels)
        {
            file << (pixel->getColor().r()) << " " << (pixel->getColor().g()) << " " << (pixel->getColor().b()) << "\n";
        }

        file.close();
    }

    friend std::ostream &operator<<(std::ostream &out, const Image &i)
    {
        out << "Image(" << i.width << ", " << i.height << ", " << i.aspectRatio << ")";
        return out;
    }

private:
    // I saw that using a vector of shared_ptr was a good idea to avoid copying the pixels
    // (I don't like copy constructors because I am bad at managing memory)
    std::vector<std::shared_ptr<Pixel>> pixels;
    const int width, height;
    const double aspectRatio;
};

#endif