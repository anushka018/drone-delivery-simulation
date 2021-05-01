/**
 * @file drone.cc
 * @author Audrey Kelly
 */
#include "drone.h"

namespace csci3081 {
Drone::Drone() {
  type_ = "drone";
  strategy = new SmartPath();
}
Drone::Drone(std::vector<float> position, std::vector<float> direction, 
                          const picojson::object& details, const std::string name, float speed, float radius,
                           float batteryCapacity, std::string pathStrategy) : 
                          PackageCarrier(position, direction, details, name, speed, radius, batteryCapacity) {
                                        
  type_ = "drone";
  if (pathStrategy == "parabolic") {
    strategy = new ParabolicPath();
  }
  else if(pathStrategy == "beeline") {
    strategy = new BeelinePath();
  }
  // default path strategy is using the smart route
  else {
    strategy = new SmartPath();
  }
}


}   // namespace csci3081