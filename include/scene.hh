#pragma once

#include "camera.hh"

class Scene
{
public:
    Scene(std::unique_ptr<Camera> &&camera) : camera(std::move(camera)) {}

    void addLight(const std::shared_ptr<Light> &light) { lights.push_back(light); }
    void addObject(const std::shared_ptr<Object> &object) { objects.push_back(object); }

    void render() { camera->render(objects, lights); }

    void save_to_ppm(const char *filename) { camera->getScreen().getImage().save_to_ppm(filename); }

    // Later on add: zoom, unzoom, move, maybe rotate

    Camera &getCamera() { return *camera; }

private:
    // Fancy memoery management
    std::unique_ptr<Camera> camera;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<Object>> objects;
};