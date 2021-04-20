/**
 * @file robot.cc
 * @author Audrey Kelly
 */
#include "robot.h"
#include <iterator>

namespace csci3081 {

Robot::Robot(std::vector<float> position, std::vector<float> direction, 
                          const picojson::object& details, const std::string name, float speed, float radius, float batteryCapacity) : 
                          PackageCarrier(position, direction, details, name, speed, radius, batteryCapacity) {
                                        
  type_ = "robot";
}


}   // namespace csci3081