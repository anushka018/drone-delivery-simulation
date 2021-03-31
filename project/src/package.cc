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

  position_ = Vector3D(position);
  direction_ = Vector3D(direction);                                     
  type_ = "package";
  weight_ = weight;
  destination = Vector3D(); // Initialized to origin of graph until delivery is scheduled
  recipient = nullptr;
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

}   // namespace csci3081