/**
 * @file customer.cc
 * @author Audrey Kelly
 */
#include "customer.h"

namespace csci3081 {
    Customer::Customer(std::vector<float> position, std::vector<float> direction,
                        const picojson::object& details, const std::string name, float speed, float radius) 
                        : EntityBase(details, position, direction, name, speed, radius) {
        type_ = "customer";
    }
}   // namespace csci3081
