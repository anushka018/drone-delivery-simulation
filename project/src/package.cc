/**
 * @file package.cc
 * @author Audrey Kelly
 */
#include "package.h"

namespace csci3081 {
    Package::Package(std::vector<float> position, std::vector<float> direction,
                        const picojson::object& details, const std::string name,
                            float weight, float speed, float radius) 
                    : EntityBase(details, position, direction, name, speed, radius) {
                                        
  type_ = "package";
  weight_ = weight;
  destination = Vector3D(); // Initialized to origin of graph until delivery is scheduled
  recipient = nullptr;
  isDropped = false;
}
    float Package::GetWeight() {
        return weight_;
    }

    Customer* Package::GetCustomer() {
        return recipient;
    }

    void Package::SetCustomer(Customer* dest) {
        isDynamic = true;
        recipient = dest;
    }

    Vector3D& Package::GetDestination() {
        return destination;
    }

    void Package::SetDestination(Vector3D dest) {
        destination = dest;
    }

    void Package::SetIsDropped(bool isDropped_) { 
        isDropped = isDropped_;
    }
    
    bool Package::GetIsDropped(){
        return isDropped;
    }
}   // namespace csci3081