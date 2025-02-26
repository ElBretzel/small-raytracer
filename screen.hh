#ifndef SCREEN_HH
#define SCREEN_HH

#include "basis.hh"
#include "color3.hh"
#include "image.hh"

double DEFAULT_ASPECT_RATIO = 16.0 / 9.0;
double DEFAULT_WIDTH = 800.0;

class Screen
{
public:

    Screen(const std::shared_ptr<Basis> &basis, int focal_length, double fov)
        : cameraBasis(basis),
          image(std::make_unique<Image>(DEFAULT_WIDTH, DEFAULT_ASPECT_RATIO))
    {
        // Because I am bad at C++, I just copied past from the previous constructor

        setFov(fov, focal_length);
        position = cameraBasis->getOrigin() + (cameraBasis->getZ() * focal_length) + (cameraBasis->getY() * (screen_height / 2.0)) - (cameraBasis->getX() * (screen_width / 2.0));
    }

    Screen(std::unique_ptr<Image> image, const std::shared_ptr<Basis> &basis, int focal_length, double fov)
        : cameraBasis(basis),
          image(std::move(image))
    {
        // Because I am bad at C++, I just copied past from the previous constructor

        setFov(fov, focal_length);
        position = cameraBasis->getOrigin() + (cameraBasis->getZ() * focal_length) + (cameraBasis->getY() * (screen_height / 2.0)) - (cameraBasis->getX() * (screen_width / 2.0));
    }

    Point3 getPixelPosition(int i, int j) const
    {
        // Like a scanline in CRT monitors
        return position + (cameraBasis->getX() * pixel_size * i) - (cameraBasis->getY() * pixel_size * j);
    }

    Basis getBasis() const { return *cameraBasis; }

    void setFov(double fov, double focal_length)
    {
        // Taking left-hand rule of the camera basis
        // Screen height = tan(fov / 2) = height / focal_length (tan(o) = opp/adj)
        screen_height = std::tan(fov / 2.0) * focal_length;
        // I just reusing the aspect ratio of the image because I am too lazy to handle vertical fov
        screen_width = screen_height * image->getAspectRatio();
        pixel_size = screen_width / image->getWidth();
    }

    Point3 getPosition() const { return position; }

    Image &getImage() const { return *image; }

    friend std::ostream &operator<<(std::ostream &out, const Screen &s)
    {
        out << "Screen(" << s.cameraBasis << ", " << s.position << ", " << s.screen_width << ", " << s.screen_height << ", " << s.pixel_size << ")";
        return out;
    }

protected:
    std::shared_ptr<Basis> cameraBasis;
    std::unique_ptr<Image> image;
private:
    Point3 position;
    double screen_width;
    double screen_height;
    double pixel_size;
};

#endif