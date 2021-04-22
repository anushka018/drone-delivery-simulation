/**
 * @file drone_factory.cc
 * @author Audrey Kelly
 */
#include "drone_factory.h"
#include "picojson.h"

namespace csci3081 { 
    DroneFactory::DroneFactory() {};

    IEntity* DroneFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type").compare("drone") == 0) {
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
            float speed = 30.0; 
            contains = JsonHelper::ContainsKey(val, "speed");
            if (contains) {
                speed = (float) JsonHelper::GetDouble(val, "speed");
            }
            float batteryCapacity = 10000.0;
            contains = JsonHelper::ContainsKey(val, "battery_capacity");
            if (contains) {
                batteryCapacity = (float) JsonHelper::GetDouble(val, "battery_capacity");
            }
            contains = JsonHelper::ContainsKey(val, "path");
            std::string pathType = "";
            if (contains) {
                pathType = JsonHelper::GetString(val, "path");
            }
            picojson::object& modified = const_cast<picojson::object&>(val);
            JsonHelper::AddStringToJsonObject(modified, "color","0x58ff3b");
            Drone* drone = new Drone(position, direction, modified, name, speed, radius, batteryCapacity, pathType);
            return new DroneDecorator(drone);
        }
        return nullptr;
    }

}   // namespace csci3081
