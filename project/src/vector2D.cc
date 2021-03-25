/**
 * @file vector2D.cc
 * @author Audrey Kelly
 */
#include "vector2D.h"

namespace csci3081 {
    Vector2D::Vector2D(float newX, float newZ) : Vector3D(newX, 0.0, newZ) {};

    Vector2D::Vector2D(std::vector<float> vec) {
        if (vec.size() >= 3) {
            x = vec.at(0);
            y = 0.0;
            z = vec.at(1);
        }
        else {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
    }

    Vector2D Vector2D::operator+(const Vector2D& other) {
        return Vector2D(x + other.x, z + other.z);
    }

    Vector2D& Vector2D::operator+=(const Vector2D& other) {
        x += other.x;
        z += other.z;
        return *this;
    }

    Vector2D Vector2D::operator-(const Vector2D& other) {
        return Vector2D(x - other.x, z - other.z);
    }

    Vector2D& Vector2D::operator-=(const Vector2D& other) {
        x -= other.x;
        z -= other.z;
        return *this;
    }

    Vector2D Vector2D::operator*(const float scalar) {
        return Vector2D(x * scalar, z * scalar);
    }

    Vector2D& Vector2D::operator*=(const float scalar) {
        x *= scalar;
        z *= scalar;
        return *this;
    }

    Vector2D& Vector2D::operator=(const Vector2D& source) {
        x = source.x;
        z = source.z;
        return *this;
    }

    void Vector2D::Display() {
        std::cout << std::fixed <<std::setprecision(3) << "(" << x << ", " << z << ")" << std::endl;
    }

}   // namespace csci3081