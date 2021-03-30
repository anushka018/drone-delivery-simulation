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
  currentPackage = nullptr;
  path = {};
}

void PackageCarrier::Update(float dt) {
  // PackageCarrier cannot move without battery power
  if (!(battery->IsDead())) {
    SetDirection(path[pathIndex]);
    position_ += Vector3D((direction_ * speed_) * dt);
    posVector = position_.GetVector();
    // If PackageCarrier is carrying package or is within package's radius, it updates the package's position to match its own
    if (hasPackage) {
      CarryPackage();
    }
    if (!hasPackage && position_.GetDistance(Vector3D(currentPackage->GetPosition())) <= (currentPackage->GetRadius() + radius_)) {
      hasPackage = true;
      CarryPackage();
      //notify the observers that the package is on its way
      picojson::object eventObj = JsonHelper::CreateJsonNotification();
      JsonHelper::AddStringToJsonObject(eventObj, "value", "en route");
      picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
      Notify(eventVal, *currentPackage);


    }
    battery->DecreaseCharge(dt);
   //std::cout << battery->GetBatteryReserve() << std::endl;

  }
}

void PackageCarrier::CarryPackage() {
    currentPackage->SetSpeed(speed_);
    currentPackage->SetPosition(posVector);
    currentPackage->SetDirection(dirVector);
    // If package position has reached its destination, PackageCarrier should deliver package and stop moving
    if (position_.GetDistance(currentPackage->GetDestination()) <= currentPackage->GetRadius()) {
      currentPackage->SetPosition({0,-500,0});
      hasPackage = false;
      // Remove package from list of scheduled deliveries
      packages.erase(packages.begin());
      // Continue to next package to deliver if there are more scheduled
      if (packages.size() > 0) {
        currentPackage = packages.at(0);
      }
      //notify the observers that the package has been delivered
      picojson::object eventObj = JsonHelper::CreateJsonNotification();
      JsonHelper::AddStringToJsonObject(eventObj, "value", "delivered");
      picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
      Notify(eventVal, *currentPackage);

      picojson::object eventObj2 = JsonHelper::CreateJsonNotification();
      JsonHelper::AddStringToJsonObject(eventObj2, "value", "idle");
      picojson::value eventVal2 = JsonHelper::ConvertPicojsonObjectToValue(eventObj2);
      Notify(eventVal2, *this);

    }
    
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
  packages.push_back(package);
  currentPackage = packages.at(0);
  currentPackage = package;
  //notify the observers that the package has been scheduled
  picojson::object eventObj = JsonHelper::CreateJsonNotification();
  JsonHelper::AddStringToJsonObject(eventObj, "value", "scheduled");
  picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
  Notify(eventVal, *currentPackage);

  picojson::object eventObj2 = JsonHelper::CreateJsonNotification();
  JsonHelper::AddStringToJsonObject(eventObj2, "value", "moving");
  std::vector< std::vector<float> >::iterator it = std::find(path.begin(), path.end(), currentPackage->GetPosition());
  int index = std::distance(path.begin(), it);
  JsonHelper::AddStdVectorVectorFloatToJsonObject(eventObj2, "path", path);
  picojson::value eventVal2 = JsonHelper::ConvertPicojsonObjectToValue(eventObj2);
  Notify(eventVal2, *this);

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