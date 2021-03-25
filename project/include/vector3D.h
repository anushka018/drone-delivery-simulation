/**
 * @file vector3D.h
 * @author Audrey Kelly
 */
#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <iostream>
#include <iomanip>
#include <vector>
#include<math.h>

namespace csci3081 {
/**
 * @brief The class used to implement 3-dimensional vectors for the position, direction, and movement 
 * of entities in the delivery simulation.
 * 
 * @details 3D Vectors will be used for entities in the simulation that can fly (i.e. Drones for Iteration 1).
 * 
 */
class Vector3D {
 public:
    /**
     * @brief Default constructor a new Vector 3D object. Can take optional floating points
     * indicating each coordinates, otherwise sets all coordinates to 0.0.
     * 
     * @param[in] newX as the x-coordinate of the vector
     * @param[in] newY as the y-coordinate of the vector
     * @param[in] newZ as the z-coordinate of the vector
     */
    Vector3D(float newX = 0.0, float newY = 0.0, float newZ = 0.0);
    /**
     * @brief Construct a new Vector 3D object using a standard library vector of float type. 
     * 
     * @param[in] std::vector<float> vec with coordinates for the Vector3D object
     */
    Vector3D(std::vector<float> vec);
    /**
     * @brief Returns the x-coordinate of the vector
     * 
     * @return float x-coordinate
     */
    float GetX();
    /**
     * @brief Returns the y-coordinate of the vector
     * 
     * @return float y-coordinate
     */
    float GetY();
    /**
     * @brief Returns the z-coordinate of the vector
     * 
     * @return float z-coordinate
     */
    float GetZ();
    /**
     * @brief Finds the sum of two Vector3D objects
     * 
     * @param[in] other constant Vector3D& for the second addend in additions
     * @return Vector3D object for the sum of this object and second added together
     */
    Vector3D operator+(const Vector3D& other);
    /**
     * @brief Increments this Vector3D object by the specified Vector amount
     * 
     * @param[other] constant Vector3D& to increment object's coordinates
     * @return Vector3D& reference to this object
     */
    Vector3D& operator+=(const Vector3D& other);
    /**
     * @brief Finds the vector difference between two Vector3D objects
     * 
     * @param[in] Second Vector3D object for the minuend
     * @return new Vector3D object for the difference of this object and second
     */
    Vector3D operator-(const Vector3D& other);
    /**
     * @brief Decrement this Vector3D object by the specified Vector amount
     * 
     * @param[in] Vector3D to decrement object's coordinates
     * @return Vector3D& reference to this object with decremented coordinates
     */
    Vector3D& operator-=(const Vector3D& other);
    /**
     * @brief Multiplication operator which returns the product of the scalar with the Vector3D
     * 
     * @param[in] scalar to multiply Vector3D coordinates
     * @return new Vector3D object with multiplied coordinates
     */
    Vector3D operator*(const float scalar);
    /**
     * @brief Perform scalar multiplication of a 3D vector
     * 
     * @param[in] scalar to multiply the vector's coordinates
     * @return Vector3D& reference to this object with multiplied coordinates
     */
    Vector3D& operator*=(const float scalar);
    /**
     * @brief Assignment Operator for 3D vectors
     * 
     * @param[in] source Vector3D object to copy coordinates
     * @return Vector3D& reference to this object with copied coordinates
     */
    Vector3D& operator=(const Vector3D& source);
    /**
     * @brief Get the scalar magnitude (length) of the vector. The magnitude will always be greater than or equal to zero.
     * 
     * @return float representing magnitude of vector
     */
    float GetMagnitude();
    /**
     * @brief Transforms vector into a Unit Vector with the same direction but with a magnitude of 1.0.
     * In the case that the vector has magnitude 0.0, the method does nothing and returns the zero vector.
     * 
     * @return Vector3D& Unit Vector of this Object
     */
    Vector3D& Normalize();
    /**
     * @brief Checks if the Vector has been turned into a Unit Vector or has magnitude 1.0
     * 
     * @return true if Vector has a magnitude/length of 1.0
     * @return false if Vector has a magnitude/length other than 1.0
     */
    bool IsNormalized();
    /**
     * @brief Finds the scalar distance between this vector and the other vector parameter
     * 
     * @param[in] other Vector to calculate distance to
     * @return float representing the distance from this vector object to the other vector
     */
    float GetDistance(const Vector3D& other);
    /**
     * @brief Converts vector into a std::vector<float> of length three
     * 
     * @return std::vector<float>&  representation of Vector3D object
     */
    std::vector<float> GetVector() const;
    /**
     * @brief Prints vector into string representation in format "( x , y , z )".  
     * Intended purpose is for debugging. 
     */
    virtual void Display();

 protected:
    float x;
    float y;
    float z;
};

}   // namespace csci3081

#endif  // VECTOR_3D_H