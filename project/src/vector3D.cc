/**
 * @file vector3D.cc
 * @author Audrey Kelly
 */
#include "vector3D.h"

namespace csci3081 {
    Vector3D::Vector3D(float newX, float newY, float newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }

    Vector3D::Vector3D(std::vector<float> vec) {
        if (vec.size() == 3) {
            x = vec.at(0);
            y = vec.at(1);
            z = vec.at(2);
        }
        else { // If vector is invalid, initialize object to origin
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
    }

    float Vector3D::GetX() {
        return x;
    }

    float Vector3D::GetY() {
        return y;
    }

    float Vector3D::GetZ() {
        return z;
    }

    Vector3D Vector3D::operator+(const Vector3D& other) {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D& Vector3D::operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D Vector3D::operator-(const Vector3D& other) {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*(const float scalar) {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D& Vector3D::operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3D& Vector3D::operator=(const Vector3D& source) {
        x = source.x;
        y = source.y;
        z = source.z;
        return *this;
    }

    float Vector3D::GetMagnitude() {
        return sqrt((x*x) + (y*y) + (z*z));
    }

    Vector3D& Vector3D::Normalize() {
        if (GetMagnitude() != 0.0) {    // If the vector has length 0.0, it is not changed by Normalize()
            double mag = (double) GetMagnitude();
            x /= mag;
            y /= mag;
            z /= mag;
        }
        return *this;
    }

    bool Vector3D::IsNormalized() {
        if (GetMagnitude() == 1.0) {
            return true;
        }
        return false;
    }

    float Vector3D::GetDistance(const Vector3D& other) {
        Vector3D dist = *this - other;
        return dist.GetMagnitude();
    }
  
    std::vector<float> Vector3D::GetVector() const {
        std::vector<float> vec;
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
        return vec;
    }

    void Vector3D::Display() {
        std::cout << std::fixed << std::setprecision(3) << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
}   // namespace csci3081