#ifndef VECTOR3_HH
#define VECTOR3_HH

#include <cmath>
#include <iostream>

// Lot of Vector3 utils

class Vector3
{
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}

    Vector3& operator=(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(double factor) const
    {
        return Vector3(x * factor, y * factor, z * factor);
    }

    Vector3 operator/(double factor) const
    {
        return Vector3(x / factor, y / factor, z / factor);
    }

    double dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3 &other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    double length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    double lengthSquared() const
    {
        return x * x + y * y + z * z;
    }

    Vector3 normalize() const
    {
        return *this / length();
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v)
    {
        return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    }

    static const Vector3 UP;
    static const Vector3 RIGHT;
    static const Vector3 FORWARD;
    static const Vector3 CAM_DIR;
    static const Vector3 ZERO;
    static const Vector3 ONE;

protected:
    double x, y, z;
};

const Vector3 Vector3::UP = Vector3(0, 1, 0);
const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);
const Vector3 Vector3::CAM_DIR = Vector3(0, 0, 1);
const Vector3 Vector3::ZERO = Vector3(0, 0, 0);
const Vector3 Vector3::ONE = Vector3(1, 1, 1);

#endif