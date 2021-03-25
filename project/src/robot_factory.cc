/**
 * @file robot_factory.cc
 * @author Audrey Kelly
 */
#include "robot_factory.h"

namespace csci3081 {
    RobotFactory::RobotFactory() {};

    IEntity* RobotFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type").compare("robot") == 0) {
            bool contains = false;
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");

            contains = JsonHelper::ContainsKey(val, "name");
            std::string name = "";
            if (contains) {
                name = JsonHelper::GetString(val, "name");
            }
            float radius = 1.0;
            contains = JsonHelper::ContainsKey(val, "radius");
            if (contains) {
                radius = (float) JsonHelper::GetDouble(val, "radius"); 
            }
            float speed = 0.0; 
            contains = JsonHelper::ContainsKey(val, "speed");
            if (contains) {
                speed = (float) JsonHelper::GetDouble(val, "speed");
            }
            float batteryCapacity = 10000.0;
            contains = JsonHelper::ContainsKey(val, "battery_capacity");
            if (contains) {
                batteryCapacity = (float) JsonHelper::GetDouble(val, "battery_capacity");
            }
            
            return new Robot(position, direction, val, name, speed, radius, batteryCapacity);
        }
        return nullptr;
    }

}   // namespace csci3081