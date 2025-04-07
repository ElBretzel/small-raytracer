#include <iostream>

#include "light.hh"
#include "object.hh"
#include "scene.hh"

#define PI 3.14159265358979323846

int main(void)
{
    auto fov = PI / 2.0;
    auto width = 2000;
    auto aspect_ratio = 16.0 / 9.0;
    auto focal_length = 1.0;

    auto image = std::make_unique<Image>(width, aspect_ratio);
    auto camera = std::make_unique<Camera>(std::move(image), focal_length, fov);

    auto red = Color3::from_rgb(255, 0, 0);
    auto green = Color3::from_rgb(0, 255, 0);
    auto blue = Color3::from_rgb(0, 0, 255);

    auto radius = 1.0;

    auto sphere2 = std::make_shared<Sphere>(Point3(1, 1, 8), radius, red);
    auto sphere3 = std::make_shared<Sphere>(Point3(-1, 1, 4), radius, green);

    auto light1 = std::make_shared<PointLight>(Point3(0, 0, 0), 0.5);
    auto light2 = std::make_shared<PointLight>(Point3(-8, 3, 0), 0.5);
    Scene scene(std::move(camera));
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addLight(light1);
    //scene.addLight(light2);

    scene.render(3);
    scene.save_to_ppm("output.ppm");

    return 0;
}