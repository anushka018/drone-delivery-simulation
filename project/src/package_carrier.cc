/**
 * @file package_carrier.cc
 * @author Audrey Kelly
 */
#include "package_carrier.h"
#include <iterator>
#include <json_helper.h>

namespace csci3081 {

PackageCarrier::PackageCarrier(std::vector<float> position, std::vector<float> direction, 
                          const picojson::object& details, const std::string name, float speed, float radius, float batteryCapacity) : 
                          EntityBase(details, position, direction, name, speed, radius) {
                                
  battery = new Battery(batteryCapacity);
  pathIndex = 0;
  hasPackage = false;
  package_ = nullptr;
  path = {};
  event = JsonHelper::CreateJsonNotification();

}

void PackageCarrier::Update(float dt) {
  // PackageCarrier cannot move without battery power
  if (!(battery->IsDead())) {
    SetDirection(path[pathIndex]);
    position_ += Vector3D((direction_ * speed_) * dt);
    posVector = position_.GetVector();
    // If PackageCarrier is carrying package or is within package's radius, it updates the package's position to match its own
    if (hasPackage || position_.GetDistance(Vector3D(package_->GetPosition())) <= (package_->GetRadius() + radius_)) {
      hasPackage = true;
      CarryPackage();
      //change json object values to en route
      event = JsonHelper::CreateJsonNotification();
      JsonHelper::AddStringToJsonObject(event, "value", "en route");
      JsonHelper::ConvertPicojsonObjectToValue(event);


    }
    battery->DecreaseCharge(dt);
  }
}

void PackageCarrier::CarryPackage() {
    package_->SetSpeed(speed_);
    package_->SetPosition(posVector);
    package_->SetDirection(dirVector);
    // If package position has reached its destination, PackageCarrier should deliver package and stop moving
    if (position_.GetDistance(package_->GetDestination()) <= package_->GetRadius()) {
      package_->SetPosition({0,-500,0});
      hasPackage = false;
    }
    //change json object values to delivered
    event = JsonHelper::CreateJsonNotification();
    JsonHelper::AddStringToJsonObject(event, "value", "delivered");
    JsonHelper::ConvertPicojsonObjectToValue(event);

}

void PackageCarrier::SetDirection(const std::vector<float>& dest) {
    Vector3D convertDest = Vector3D(dest);
    // If the PackageCarrier's radius is within a 1.0 meter radius of their current destination, they have reached that point
    if (convertDest.GetDistance(position_)  <= radius_) {
      if (pathIndex < (path.size() - 1)) {
        direction_ = path[++pathIndex];
      }
      else { // path index out of bounds, PackageCarrier should stop moving
        speed_ = 0.0;
      }

    }
    direction_ = convertDest - position_;
    direction_.Normalize();
    dirVector = direction_.GetVector();
}

void PackageCarrier::AssignPackage(Package* package) {
  isDynamic = true;
  package_ = package;
  //change json object values to scheduled
  event = JsonHelper::CreateJsonNotification();
  JsonHelper::AddStringToJsonObject(event, "value", "scheduled");
  JsonHelper::ConvertPicojsonObjectToValue(event);

}

std::vector< std::vector<float> > PackageCarrier::GetPath() {
  return path;
}

void PackageCarrier::SetPath(const std::vector< std::vector<float> > newPath) {
  path = newPath;
}

Battery* PackageCarrier::GetBattery() {
  return battery;

}

PackageCarrier::~PackageCarrier() {
  delete battery;
}

}   // namespace csci3081