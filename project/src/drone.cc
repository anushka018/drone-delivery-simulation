/**
 * @file drone.cc
 * @author Audrey Kelly
 */
#include "drone.h"
#include <iterator>

namespace csci3081 {

Drone::Drone(std::vector<float> position, std::vector<float> direction, 
                          const picojson::object& details, const std::string name, float speed, float radius, float batteryCapacity) : 
                          PackageCarrier(position, direction, details, name, speed, radius, batteryCapacity) {
                                        
  position_ = Vector3D(position);
  direction_ = Vector3D(direction);   
  type_ = "drone";
}


}   // namespace csci3081