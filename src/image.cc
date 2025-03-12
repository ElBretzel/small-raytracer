#include "image.hh"

Image::Image(int width, double aspectRatio) : width(width), height((int)width / aspectRatio), aspectRatio(aspectRatio)
{

    // Dummy pixel (so I can use the same index for the pixels)
    // There might be a cleaner way to do this
    pixels.reserve(width * height);
    for (int i = 0; i < width * height; i++)
    {
        pixels.push_back(std::make_shared<Pixel>());
    }
}

void Image::create_debug_gradient()
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

void Image::save_to_ppm(const char *filename) const
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