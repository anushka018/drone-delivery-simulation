/**
 * @file robot.h
 * @author Audrey Kelly
 */
#include "entity_base.h"
#include "package_carrier.h"
#include <vector>
#include <string>
#include "battery.h"
#include "package.h"

#ifndef ROBOT_H
#define ROBOT_H

namespace csci3081 {
/**
 * @brief This is the entity class representing robots in the simulation.
 * 
 * @details robots are responsible for picking up the package and bringing it to the customer.
 * 
 */
class Robot : public PackageCarrier {
 public:
   /**
    * @brief Construct a new robot entity
    * 
    * @param[in] details for the picojson object
    * @param[in] position of entity in (x, y, z) float vector
    * @param[in] direction of entity in (x, y, z) float vector
    * @param[in] name of robot
    * @param[in] speed in meters per second (default is 0.0)
    * @param[in] radius in meters (default is 1.0)
    */
    Robot(std::vector<float> position, std::vector<float> direction,
            const picojson::object& details, const std::string name = "Default robot",
                float speed = 0.0, float radius = 1.0, float batteryCapacity = 10000.0); 
};

}   // namespace csci3081

#endif   // ROBOT_H