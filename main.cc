#include <iostream>

#include "scene.hh"

#define PI 3.14159265358979323846

int main(void)
{
    auto image = std::make_unique<Image>(800, 16.0 / 9.0);
    auto camera = std::make_unique<Camera>(std::move(image), 1.0, PI/2.);
    auto sphere = std::make_shared<Sphere>(Point3(0, 0, 10), 1, Color3::from_rgb(255, 0, 0));

    Scene scene(std::move(camera));
    scene.addObject(sphere);

    scene.render();
    scene.save_to_ppm("output.ppm");

    return 0;
}