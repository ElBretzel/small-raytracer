#include "camera.hh"
#include "ray.hh"

void Camera::render(const std::vector<std::shared_ptr<Object>> objects, const std::vector<std::shared_ptr<Light>> lights, int max_reflect_iter)
{
    for (int i = 0; i < screen->getImage().getWidth(); i++)
    {
        for (int j = 0; j < screen->getImage().getHeight(); j++)
        {
            // Get the pixel position in the WORLD space
            Vector3 pixelPosition = screen->getPixelPosition(i, j);
            // Create the ray in the WORLD space. Direction is normalized to have a unit vector (formula is origin + t * direction)
            Ray ray = Ray(basis->getOrigin(), (pixelPosition - basis->getOrigin()).normalize());
            // Cast the ray and get the color. Right now cast returns a color
            screen->getImage().setPixel(Point2(i, j), ray.cast(objects, lights, max_reflect_iter, 0));
        }
    }
}