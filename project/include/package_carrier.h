/**
 * @file package_carrier.h
 * @author Audrey Kelly
 */
#ifndef PACKAGE_CARRIER_H
#define PACKAGE_CARRIER_H

#include "entity_base.h"
#include "path_strategy.h"
#include "observer_helper.h"
#include "battery.h"
#include "package.h"
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <json_helper.h>


namespace csci3081 {
/**
 * @brief This is an abstract class to represent entities in the simulation responsible for picking up packages and delivering them to customers
 * 
 * @details Drone and Robot entities are derived from this class
 * 
 */
class PackageCarrier : public EntityBase {
 public:
  PackageCarrier();
   /**
    * @brief Construct a new Package Carrier entity
    * 
    * @param[in] details for the picojson object
    * @param[in] position of entity in (x, y, z) float vector
    * @param[in] direction of entity in (x, y, z) float vector
    * @param[in] name of Drone
    * @param[in] speed in meters per second (default is 0.0)
    * @param[in] radius in meters (default is 1.0)
    * @param[in] batteryCapacity in seconds (default is 10000)
    */
    PackageCarrier(std::vector<float> position, std::vector<float> direction,
            const picojson::object& details, const std::string name = "Default Package Carrier",
                float speed = 0.0, float radius = 1.0, float batteryCapacity = 10000.0);
                
    /**
     * @brief Moves the entity via Eulerian Integration with the given time interval dt
     * 
     * @param[in] dt time interval in seconds
     */
    virtual void Update(float dt) override;
    /**
     * @brief Get the route the package carrier is currently following for package delivery
     * 
     * @return a vector of (x,y,z) coordinate vectors that form a path avoiding buildings on the map
     */
    virtual std::vector< std::vector<float> > GetPath();
    /**
     * @brief Set the path for the carrier to follow for package delivery
     * 
     * @param[in] newPath: a list of vectors containing the float coordinate vectors of the path
     */
    virtual void SetPath(const std::vector< std::vector<float> >& newPath);
    /**
     * @brief Create the path using the drone or robot's assigned path strategy
     * 
     * @param[in]: carrierPosition, the origin of the drone or robot before delivery
     * @param[in]: packagePosition, the position of the package to be picked up
     * @param[in]: customerPosition, the destination for the package
     * @param[in]: graph, an optional IGraph* only used for the smart route strategy
     * 
     * @return std::vector< std::vector<float> >: a complete path for package carrier to follow from origin to package to customer
     */
    virtual std::vector< std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph = nullptr);
    /**
     * @brief Set the package pointer for the carrier
     * 
     * @param[in] package: the pointer to the package the drone is carrying
     */
    virtual void AssignPackage(Package* package);
    /**
     * @brief Get the Battery of the carrier's engine
     * 
     * @return Battery* pointer to drone battery
     */
    virtual Battery* GetBattery();
    /**
     * @brief Sets the direction of the package carrier to the given coordinate point
     * 
     * @details Overrides the SetDirection from the base class EntityBase. Takes in the new destination and checks
     * if carrier is already at given destination. If so, the method does not change the package carrier's direction. Else, the direction is
     * calculated using Vector math: direction = destination - position. Finally, the direction is normalized before being set
     * as the carrier's new direction for movement. 
     * 
     * @param[in] destination vector with (x,y,z) float coordinates
     */
    void SetDirection(const std::vector<float>& dest) override;
    /**
     * @brief Destroy the carrier object and its dynamically allocated battery
     * 
     */
    virtual ~PackageCarrier();

 protected:
    Battery* battery;
    Package* currentPackage;
    std::vector<Package*> packages;
    std::vector< std::vector<float> > path;
    PathStrategy* strategy;
    ObserverHelper* observerHelper;
    int pathIndex;
    bool hasPackage;
    bool firstTimeDead = false;
    /**
     * @brief Pick up and move the package along with the carrier.  
     * 
     * @details Sets the position and direction of the package to the carrier's to match the movement. 
     */
    void CarryPackage();
    /**
     * @brief Get the path from the previous package's destination to the next scheduled package
     * 
     * @param path: input and output list of 3D float vectors for package carrier to follow 
     */
    void GetNextPackagePath(std::vector< std::vector<float> >& path);
};

}   // namespace csci3081

#endif   // PACKAGE_CARRIER_H