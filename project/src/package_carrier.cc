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
  std::vector< std::vector<float> >::iterator start = std::find(path.begin(), path.end(), currentPackage->GetPosition());
  std::vector< std::vector<float> >::iterator end;
  if (packages.size() > 1) {
    end = std::find(start, path.end(), (currentPackage->GetDestination()).GetVector());
  }
  else {
    end = path.end();
  }
  int size = std::distance(start, end);
  std::vector< std::vector<float> > customerPath(size);
  std::copy(start, end, customerPath.begin());
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
  if (!firstTimeDead && battery->IsDead()) {
      for (Package* package : packages) {
        package-> SetIsDropped(true);
      }
      packages.erase(packages.begin());
      firstTimeDead = true; 
      // Notify observers that drone/robot has stopped moving
      picojson::value eventVal = CreateNotification("idle");
      Notify(eventVal, *this);

      //change the height of the package
      if (hasPackage) {
        float x_position = currentPackage->GetPosition().at(0);
        float z_position = currentPackage->GetPosition().at(2);
        currentPackage->SetPosition({x_position, 250 , z_position});
      } 
  }
}
 
void PackageCarrier::GetNextPackagePath(std::vector< std::vector<float> >& packagePath) {
  // Get path from last package's destination to next package
  std::vector< std::vector<float> >::iterator start = std::find(path.begin(), path.end(), (currentPackage->GetDestination()).GetVector());
  std::vector< std::vector<float> >::iterator end = std::find(start, path.end(), packages.at(1)->GetPosition());
  int size = std::distance(start, end);
  packagePath.resize(size);
  std::copy(start, end, packagePath.begin());
}
 
void PackageCarrier::CarryPackage() {
    currentPackage->SetSpeed(speed_);
    currentPackage->SetPosition(posVector);
    currentPackage->SetDirection(dirVector);
    // If package position has reached its destination, PackageCarrier should deliver package and stop moving
    if (position_.GetDistance(currentPackage->GetDestination()) <= currentPackage->GetRadius()) {
      currentPackage->SetPosition({0,-500,0});
      hasPackage = false;
      // Notify observers that package has been delivered
      picojson::value eventVal = CreateNotification("delivered");
      Notify(eventVal, *currentPackage);
      // Continue to next package to deliver if there are more scheduled
      if (packages.size() > 1) {
        std::vector< std::vector<float> > packagePath;
        GetNextPackagePath(packagePath);
        // Remove package from list of scheduled deliveries
        packages.erase(packages.begin());
        currentPackage = packages.at(0);
        // notify observers that package carrier is moving toward package
        eventVal = CreateNotification("moving", packagePath);
        Notify(eventVal, *this);
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
  Notify(eventVal, *package);
  if (packages.size() == 1) {
    // find segment of path from carrier origin to package
  std::vector< std::vector<float> >::iterator end = std::find(path.begin(), path.end(), currentPackage->GetPosition());
  int size = std::distance(path.begin(), end);
  std::vector< std::vector<float> > packagePath(size);
  std::copy(path.begin(), end, packagePath.begin());
  packagePath.push_back(currentPackage->GetPosition());
  // notify observers that package carrier is moving toward package
  eventVal = CreateNotification("moving", packagePath);
  Notify(eventVal, *this);
  } 
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

void PackageCarrier::SetPath(const std::vector< std::vector<float> >& newPath) {
  path = newPath;
}

std::vector< std::vector<float> > PackageCarrier::CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) {
  return strategy->CreatePath(carrierPosition, packagePosition, customerPosition, graph);
}
 
Battery* PackageCarrier::GetBattery() {
  return battery;
}

PackageCarrier::~PackageCarrier() {
  delete battery;
  delete strategy;
}
 
}   // namespace csci3081