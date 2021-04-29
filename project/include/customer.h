/**
 * @file customer.h
 * @author Audrey Kelly
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "entity_base.h"

namespace csci3081 {
/**
 * @brief The class to represent Customers in the simulation.
 * 
 */
class Customer : public EntityBase {
 public:
   /**
    * @brief Construct a new Customer entity
    * 
    * @param[in] details for the picojson object
    * @param[in] position of entity in (x, y, z) float vector
    * @param[in] direction of entity in (x, y, z) float vector
    * @param[in] name of Customer
    * @param[in] speed in meters per second (default is 0.0)
    * @param[in] radius in meters (default is 1.0)
    */
   Customer(std::vector<float> position, std::vector<float> direction,
               const picojson::object& details, const std::string name = "Default Customer",
                      float speed = 0.0, float radius = 1.0); 
   
};

}  // namespace csci3081

#endif   // CUSTOMER_H
