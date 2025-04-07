#pragma once

#include "screen.hh"

#define DEFAULT_FOV 3.14159265359 / 2.0
#define DEFAULT_FOCAL_LENGTH 1.0

class Object;
class Light;

class Camera
{
public:
    // Most of these implementations will not be used
    Camera() : basis(std::make_shared<Basis>(Basis::fromZ(Vector3::CAM_DIR, Vector3::UP), Point3::ORIGIN)), screen(std::make_unique<Screen>(this->basis, 1., DEFAULT_FOV)), focal_length(1.)
    {
    }
    Camera(const Basis &basis) : basis(std::make_shared<Basis>(basis)), screen(std::make_unique<Screen>(this->basis, 1., DEFAULT_FOV)), focal_length(1)
    {
    }
    Camera(double focal_length, double fov) : basis(std::make_shared<Basis>(Basis::fromZ(Vector3::CAM_DIR, Vector3::UP), Point3::ORIGIN)), screen(std::make_unique<Screen>(this->basis, focal_length, fov)), focal_length(focal_length), fov(fov)
    {
    }

    Camera(const Basis &basis, double focal_length, double fov) : basis(std::make_shared<Basis>(basis)), screen(std::make_unique<Screen>(this->basis, focal_length, fov)), focal_length(focal_length), fov(fov)
    {
    }

    Camera(std::unique_ptr<Image> image, double focal_length, double fov) : basis(std::make_shared<Basis>(Basis::fromZ(Vector3::CAM_DIR, Vector3::UP), Point3::ORIGIN)), screen(std::make_unique<Screen>(std::move(image), basis, focal_length, fov)), focal_length(focal_length), fov(fov)
    {
    }

    Camera(const Basis &basis, std::unique_ptr<Image> image, double focal_length, double fov) : basis(std::make_shared<Basis>(basis)), screen(std::make_unique<Screen>(std::move(image), this->basis, focal_length, fov)), focal_length(focal_length), fov(fov)
    {
    }

    Point3 getPosition() const
    {
        return basis->getOrigin();
    }

    Vector3 getDirection() const
    {
        return basis->getZ();
    }

    const Basis &getBasis() const
    {
        return *basis;
    }

    Screen &getScreen() { return *screen; }

    double getFocalLength() const
    {
        return focal_length;
    }

    void setFov(double fov)
    {
        this->fov = fov;
        screen->setFov(fov, focal_length);
    }

    void setFocalLength(double focal_length)
    {
        this->focal_length = focal_length;
        screen->setFov(fov, focal_length);
    }

    void render(const std::vector<std::shared_ptr<Object>> objects, const std::vector<std::shared_ptr<Light>> lights, int max_render_iter);

    friend std::ostream &operator<<(std::ostream &out, const Camera &c)
    {
        out << "Camera(" << c.getPosition() << ", " << c.getDirection() << ", " << c.getFocalLength() << ", " << *c.screen << ")";
        return out;
    }

private:
    // Basis can be shared but screen is unique
    std::shared_ptr<Basis> basis;
    std::unique_ptr<Screen> screen;
    double focal_length = DEFAULT_FOCAL_LENGTH;
    double fov = DEFAULT_FOV;
};