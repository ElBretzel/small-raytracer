#include "screen.hh"

Screen::Screen(const std::shared_ptr<Basis> &basis, int focal_length, double fov, std::unique_ptr<Image> image)
    : cameraBasis(basis),
      image(image ? std::move(image) : std::make_unique<Image>(DEFAULT_WIDTH, DEFAULT_ASPECT_RATIO))
{
    setFov(fov, focal_length);
    position = cameraBasis->getOrigin() +
               (cameraBasis->getZ() * focal_length) +
               (cameraBasis->getY() * (screen_height / 2.0)) -
               (cameraBasis->getX() * (screen_width / 2.0));
}

void Screen::setFov(double fov, double focal_length)
{
    // Taking left-hand rule of the camera basis
    // Screen height = tan(fov / 2) = height / focal_length (tan(o) = opp/adj)
    screen_height = std::tan(fov / 2.0) * focal_length;
    // I just reusing the aspect ratio of the image because I am too lazy to handle vertical fov
    screen_width = screen_height * image->getAspectRatio();
    pixel_size = screen_width / image->getWidth();
}