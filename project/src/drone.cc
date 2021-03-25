/**
 * @file customer.cc
 * @author Audrey Kelly
 */
#include "drone.h"
#include <iterator>
#include "battery.h"
#include "package.h"

namespace csci3081 {

Drone::Drone(std::vector<float> position, std::vector<float> direction, 
                          const picojson::object& details, const std::string name, float speed, float radius) : 
                          EntityBase(details, position, direction, name, speed, radius) {
                                        
  type_ = "drone";
  battery = new Battery();
  pathIndex = 0;
  hasPackage = false;
  package_ = nullptr;
  path = {};
}

void Drone::Update(float dt) {
  // Drone cannot move without battery power
  if (!(battery->IsDead())) {
    SetDirection(path[pathIndex]);
    position_ += Vector3D((direction_ * speed_) * dt);
    posVector = position_.GetVector();
    // If Drone is carrying package or is within package's radius, it updates the package's position to match its own
    if (hasPackage || position_.GetDistance(Vector3D(package_->GetPosition())) <= (package_->GetRadius() + radius_)) {
      hasPackage = true;
      CarryPackage();
    }
    battery->DecreaseCharge(dt);
  }
}

void Drone::CarryPackage() {
    package_->SetSpeed(speed_);
    package_->SetPosition(posVector);
    package_->SetDirection(dirVector);
    // If package position has reached its destination, drone should deliver package and stop moving
    if (position_.GetDistance(package_->GetDestination()) <= package_->GetRadius()) {
      package_->SetPosition({0,-500,0});
      hasPackage = false;
    }
}

void Drone::SetDirection(const std::vector<float>& dest) {
    Vector3D convertDest = Vector3D(dest);
    // If the drone's radius is within a 1.0 meter radius of their current destination, they have reached that point
    if (convertDest.GetDistance(position_)  <= radius_) {
      if (pathIndex < (path.size() - 1)) {
        direction_ = path[++pathIndex];
      }
      else { // path index out of bounds, drone should stop moving
        speed_ = 0.0;
      }

    }
    direction_ = convertDest - position_;
    direction_.Normalize();
    dirVector = direction_.GetVector();
}

void Drone::AssignPackage(Package* package) {
  isDynamic = true;
  package_ = package;
}

std::vector< std::vector<float> > Drone::GetPath() {
  return path;
}

void Drone::SetPath(const std::vector< std::vector<float> > newPath) {
  path = newPath;
}

Battery* Drone::GetBattery() {
  return battery;

}
Drone::~Drone() {
  delete battery;
}

}   // namespace csci3081