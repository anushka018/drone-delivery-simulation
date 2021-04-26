/**
 * @file drone.h
 * @author Audrey Kelly
 */
#include "entity_base.h"
#include "package_carrier.h"
#include <vector>
#include <string>
#include "battery.h"
#include "package.h"
#include "smart_path.h"
#include "beeline_path.h"
#include "parabolic_path.h"

#ifndef DRONE_H
#define DRONE_H

namespace csci3081 {
/**
 * @brief This is the entity class representing Drones in the simulation.
 * 
 * @details Drones are responsible for picking up the package and bringing it to the customer.
 * 
 */
class Drone : public PackageCarrier {
 public:
   /**
    * @brief Construct a new Drone entity
    * 
    * @param[in] details for the picojson object
    * @param[in] position of entity in (x, y, z) float vector
    * @param[in] direction of entity in (x, y, z) float vector
    * @param[in] name of Drone
    * @param[in] speed in meters per second (default is 0.0)
    * @param[in] radius in meters (default is 1.0)
    * @param[in] batteryCapacity in seconds (default is 10000)
    * @param[in] pathStrategy in a string (default is "smart")
    */
    Drone();
    Drone(std::vector<float> position, std::vector<float> direction,
            const picojson::object& details, const std::string name = "Default Drone",
                float speed = 0.0, float radius = 1.0, float batteryCapacity = 10000.0, std::string pathStrategy = "smart"); 
};

}   // namespace csci3081

#endif   // DRONE_H
