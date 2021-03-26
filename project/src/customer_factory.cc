/**
 * @file customer_factory.cc
 * @author Audrey Kelly
 */
#include "customer_factory.h"

namespace csci3081 {
    CustomerFactory::CustomerFactory() {};

    IEntity* CustomerFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "customer") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
            std::string name = JsonHelper::GetString(val, "name");
            
            float radius = 1.0;
            bool contains = false;
            contains = JsonHelper::ContainsKey(val, "radius");
            if (contains) {
                radius = (float) JsonHelper::GetDouble(val, "radius"); 
            }
            float speed = 0.0; 
            contains = JsonHelper::ContainsKey(val, "speed");
            if (contains) {
                speed = (float) JsonHelper::GetDouble(val, "speed");
            }
            return new Customer(position, direction, val, name, speed, radius);
        }
        return nullptr;
    }

}   // namespace csci3081