/**
 * @file package_factory.cc
 * @author Audrey Kelly
 */
#include "package_factory.h"

namespace csci3081 {
    PackageFactory::PackageFactory() {};

    IEntity* PackageFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "package") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");

            bool contains = false;
            std::string name = "";
            contains = JsonHelper::ContainsKey(val, "name");
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
            float weight = 10.0;
            contains = JsonHelper::ContainsKey(val, "weight");
            if (contains) {
                weight = (float) JsonHelper::GetDouble(val, "weight");
            }
            return new Package(position, direction, val, name, weight, speed, radius);
        }
        return nullptr;
    }
}   // namespace csci3081