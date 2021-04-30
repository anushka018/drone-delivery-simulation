/**
 * @file package_carrier.cc
 * @author Audrey Kelly
 */
#include "package_carrier.h"

namespace csci3081 {
PackageCarrier::PackageCarrier() {};

PackageCarrier::PackageCarrier(std::vector<float> position, std::vector<float> direction, 
                          const picojson::object& details, const std::string name, float speed, float radius, float batteryCapacity) : 
                          EntityBase(details, position, direction, name, speed, radius) {
  battery = new Battery(batteryCapacity);
  pathIndex = 0;
  hasPackage = false;
  currentPackage = nullptr;
  packages = {};
  path = {};
  observerHelper = nullptr;
}

void PackageCarrier::Update(float dt) {
  std::vector< std::vector<float> > customerPath;
  // PackageCarrier cannot move without battery power
  if (!(battery->IsDead())) {
    SetDirection(path[pathIndex]);
    position_ += Vector3D((direction_ * speed_) * dt);
    posVector = position_.GetVector();
    observerHelper->FindPathToCustomer(customerPath, packages);
    // If PackageCarrier is carrying package or is within package's radius, it updates the package's position to match its own
    if (hasPackage) {
      CarryPackage();
    }
    if (!hasPackage && position_.GetDistance(Vector3D(currentPackage->GetPosition())) <= (currentPackage->GetRadius() + radius_)) {
      hasPackage = true;
      CarryPackage();
      //notify the observers that the package is on its way
      observerHelper->CreateNotification("en route", currentPackage);
      // notify the observers that the drone is now moving to the customer
      observerHelper->CreateNotification("moving", customerPath);
    }
    battery->DecreaseCharge(dt);
  }
  if (!firstTimeDead && battery->IsDead()) {
      for (Package* package : packages) {
        package->SetIsDropped(true);
      }
      // Notify observers that drone/robot has stopped moving
      observerHelper->CreateNotification("idle");
      //change the height of the package so it drops
      if (hasPackage) {
        std::vector<float> packagePos = currentPackage->GetPosition();
        currentPackage->SetPosition({packagePos.at(0), 250, packagePos.at(2)});
      }
      packages.erase(packages.begin());
      firstTimeDead = true; 
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
      // Notify observers that package has been delivered
      observerHelper->CreateNotification("delivered", currentPackage);
      // Continue to next package to deliver if there are more scheduled
      if (packages.size() > 1) {
        // Remove package from list of scheduled deliveries
        std::vector< std::vector<float> > packagePath;
        observerHelper->GetNextPackagePath(packagePath, packages);
        packages.erase(packages.begin());
        currentPackage = packages.at(0);
        // notify observers that package carrier is moving toward package
        std::cout << packagePath.size() << std::endl;
        observerHelper->CreateNotification("moving", packagePath);
      }
      else {
        // Notify observers that drone has stopped moving
        observerHelper->CreateNotification("idle");
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
  if(!observerHelper) {
    observerHelper = new ObserverHelper(path, dynamic_cast<EntityBase*>(this));
  }
  // notify the observers that the package has been scheduled
  observerHelper->CreateNotification("scheduled", package);
  if (packages.size() == 1) {
    std::vector< std::vector<float> > packagePath;
    observerHelper->FindPathToPackage(packagePath, packages);
    // notify observers that package carrier is moving toward package
    observerHelper->CreateNotification("moving", packagePath);
  } 
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
  delete observerHelper;
}
 
}   // namespace csci3081