/**
 * @file package.h
 * @author Audrey Kelly
 */
#include <string>
#include "entity_base.h"
#include "customer.h"

#ifndef PACKAGE_H
#define PACKAGE_H

namespace csci3081 {
/**
 * @brief The class to represent packages in the simulation.
 * 
 */
class Package : public EntityBase {
 public:
   /**
    * @brief Construct a new Package
    *
    * @param[in] details for the picojson object
    * @param[in] position of entity in (x, y, z) float vector
    * @param[in] direction of entity in (x, y, z) float vector
    * @param[in] name of Package
    * @param[in] speed in meters per second (default is 0.0)
    * @param[in] radius in meters (default is 1.0)
    * @param[in] weight in pounds (default is 10.0)
    */
    Package(std::vector<float> position, std::vector<float> direction,
                const picojson::object& details, const std::string name = "Default Package",
                        float weight = 10.0, float speed = 0.0, float radius = 1.0); 
    /**
     * @brief Get the weight of the package in pounds
     * 
     * @return weight of package in pounds
     */
    float GetWeight();
    /**
     * @brief Get the intended customer for the package
     * 
     * @return The customer entity receiving the package
     */
    Customer* GetCustomer();
    /**
     * @brief Set the Customer recipient attribute of the package
     * 
     * @param[in] dest Customer Entity to deliver package to
     */
    void SetCustomer(Customer* dest);
    /**
     * @brief Get the destination in coordinate points for the package 
     * 
     * @return Destination for the package in a Vector3D object
     */
    Vector3D& GetDestination();
    /**
     * @brief Set the destination for the package
     * @param[in] dest Vector3D object representing coordinates of package's destination
     */
    void SetDestination(Vector3D dest);

 private:
    Vector3D destination;
    Customer* recipient;
    float weight_;
};

}   // namespace csci3081

#endif  // PACKAGE_H