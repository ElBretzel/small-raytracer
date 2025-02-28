#include <iostream>

#include "scene.hh"

#define PI 3.14159265358979323846

int main(void)
{
    auto fov = PI / 2.0;
    auto width = 800;
    auto aspect_ratio = 16.0 / 9.0;
    auto focal_length = 1.0;

    auto image = std::make_unique<Image>(width, aspect_ratio);
    auto camera = std::make_unique<Camera>(std::move(image), focal_length, fov);

    auto red = Color3::from_rgb(255, 0, 0);
    auto green = Color3::from_rgb(0, 255, 0);
    auto blue = Color3::from_rgb(0, 0, 255);

    auto radius = 1.0;

    auto sphere1 = std::make_shared<Sphere>(Point3(-2, 0, 3), radius, red);
    auto sphere2 = std::make_shared<Sphere>(Point3(0, 3, 7), radius, green);
    auto sphere3 = std::make_shared<Sphere>(Point3(5, -3, 10), radius, blue);

    Scene scene(std::move(camera));
    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);

    scene.render();
    scene.save_to_ppm("output.ppm");

    return 0;
}