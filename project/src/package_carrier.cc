/**
 * @file package_carrier.cc
 * @author Audrey Kelly
 */
#include "package_carrier.h"
#include <iterator>
#include <algorithm>
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
  // find segment of path from package to customer
  std::vector< std::vector<float> >::iterator it = std::find(path.begin(), path.end(), currentPackage->GetPosition());
  int index = std::distance(path.begin(), it);
  std::vector< std::vector<float> > customerPath(path.size() - index);
  std::copy(path.begin() + index, path.end(), customerPath.begin());
  
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
      picojson::value eventVal = CreateNotification("en route");
      Notify(eventVal, *currentPackage);
      // notify the observers that the drone is now moving to the customer
      eventVal = CreateNotification("moving", customerPath);
      Notify(eventVal, *this);
    }
    battery->DecreaseCharge(dt);
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
      // Notify observers that package has been delivered
      picojson::value eventVal = CreateNotification("delivered");
      Notify(eventVal, *currentPackage);
      // Continue to next package to deliver if there are more scheduled
      if (packages.size() > 0) {
        currentPackage = packages.at(0);
      }
      else {
        // Notify observers that drone has stopped moving
      eventVal = CreateNotification("idle");
      Notify(eventVal, *this);
      }
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
  // notify the observers that the package has been scheduled
  picojson::value eventVal = CreateNotification("scheduled");
  Notify(eventVal, *currentPackage);
  // find segment of path from carrier origin to package
  std::vector< std::vector<float> >::iterator it = std::find(path.begin(), path.end(), currentPackage->GetPosition());
  int index = std::distance(path.begin(), it);
  std::vector< std::vector<float> > packagePath(index + 1);
  std::copy(path.begin(), path.begin() + index + 1, packagePath.begin());
  // notify observers that package carrier is moving toward package
  eventVal = CreateNotification("moving", packagePath);
  Notify(eventVal, *this);
}

picojson::value PackageCarrier::CreateNotification(std::string event, const std::vector< std::vector<float> >& path) {
  picojson::object eventObj = JsonHelper::CreateJsonNotification();
  JsonHelper::AddStringToJsonObject(eventObj, "value", event);
  picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
  if (path.size() > 0) {
    JsonHelper::AddStdVectorVectorFloatToJsonObject(eventObj, "path", path);
  }
  return JsonHelper::ConvertPicojsonObjectToValue(eventObj);
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