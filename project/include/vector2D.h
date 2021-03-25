/**
 * @file vector2D.h
 * @author Audrey Kelly
 */
#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "vector3D.h"

namespace csci3081 {
/**
 * @brief The class used to implement 2-dimensional vectors for the position, direction, and movement 
 * of entities in the delivery simulation. 
 * 
 * @details 2D vectors will be used for objects in the simulation that cannot fly. Derived from Vector3D base class. 
 * Inherits all vector math methods directly from Vector3D except for the overrided Display() method and overloaded
 * arithmetic operator. 
 * 
 */
class Vector2D : public csci3081::Vector3D {
 public:
    /** 
     * @brief Construct a new Vector 2D object
     * 
     * @param[in] newX as the x-coordinate of the vector
     * @param[in] newZ as the z-coordinate of the vector
     */
    Vector2D(float newX = 0.0, float newZ = 0.0);
    /**
     * @brief Construct a new Vector 2D object using a standard library vector of float type.
     * Sets y-coordinate (1st index) of vector to be 0.0 before calling base class constructor of 
     * same signature. 
     * 
     * @param[in] std::vector<float> vec with coordinates for the Vector2D object
     */
    Vector2D(std::vector<float> vec);
    /**
     * @brief Addition operator for 2D vectors.
     * 
     * @param[in] source Vector2D object to copy coordinates
     * @return Vector2D sum of the two vectors
     */
    Vector2D operator+(const Vector2D& other);
    /**
     * @brief Increments this Vector2D object by the specified Vector amount
     * 
     * @param[other] constant Vector2D& to increment object's coordinates
     * @return Vector2D& with incremented coordinates
     */
    Vector2D& operator+=(const Vector2D& other);
    /**
     * @brief Finds the vector difference between two Vector3D objects
     * 
     * @param[in] Second Vector2D object for the minuend
     * @return new Vector2D object for the difference of the two vectors
     */
    Vector2D operator-(const Vector2D& other);
    /**
     * @brief Decrement this Vector2D object by the specified Vector amount
     * 
     * @param[in] Vector2D to decrement object's coordinates
     * @return Vector2D& with decremented coordinates
     */
    Vector2D& operator-=(const Vector2D& other);
    /**
     * @brief Multiplication operator which returns the product of the scalar with the Vector2D
     * 
     * @param[in] scalar to multiply Vector2D coordinates
     * @return new Vector2D object with multiplied coordinates
     */
    Vector2D operator*(const float scalar);
    /**
     * @brief Perform Scalar Multiplication on a 2D Vector
     * 
     * @param[in] scalar to muliply vector by
     * @return Vector2D& with multiplied coordinates
     */
    Vector2D& operator*=(const float scalar);
    /**
     * @brief Assignment Operator for 2D vectors
     * 
     * @param[in] source Vector2D object to copy coordinates
     * @return Vector2D& reference to the copied object
     */
    Vector2D& operator=(const Vector2D& source);
    /**
     * @brief Prints vector into string representation in format "( x , z )".  
     * Intended purpose is for debugging. Overrides virtual display() method in
     * Vector3D class. 
     * 
     */
    void Display() override;
};

}   // namespace csci3081

#endif  // VECTOR_2D_H