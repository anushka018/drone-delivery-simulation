/**
 * @file drone.h
 * @author Audrey Kelly
 */
#include "entity_base.h"
#include <vector>
#include <string>
#include "battery.h"
#include "package.h"

#ifndef DRONE_H
#define DRONE_H

namespace csci3081 {
/**
 * @brief This is the entity class representing Drones in the simulation.
 * 
 * @details Drones are responsible for picking up the package and bringing it to the customer.
 * 
 */
class Drone : public EntityBase {
 public:
   /**
    * @brief Construct a new Drone entity
    * 
    * @param[in] details for the picojson object
    * @param[in] position of entity in (x, y, z) float vector
    * @param[in] direction of entity in (x, y, z) float vector
    * @param[in] name of Drone
    * @param[in] speed in meters per second (default is 0.0)
    * @param[in] radius in meters (default is 1.0)
    */
    Drone(std::vector<float> position, std::vector<float> direction,
            const picojson::object& details, const std::string name = "Default Drone",
                float speed = 0.0, float radius = 1.0); 
    /**
     * @brief Moves the drone via Eulerian Integration with the given time interval dt
     * 
     * @param[in] dt time interval in seconds
     */
    void Update(float dt) override;
    /**
     * @brief Get the route the Drone is currently following for package delivery
     * 
     * @return a vector of (x,y,z) coordinate vectors that form a path avoiding buildings on the map
     */
    std::vector< std::vector<float> > GetPath();
    /**
     * @brief Set the path for the Drone to follow for package delivery
     * 
     * @param[in] newPath: a list of vectors containing the float coordinate vectors of the path
     */
    void SetPath(std::vector< std::vector<float> > newPath);
    /**
     * @brief Set the package pointer for the drone
     * 
     * @param[in] package: the pointer to the package the drone is carrying
     */
    void AssignPackage(Package* package);
    /**
     * @brief Get the Battery of the Drone's engine
     * 
     * @return Battery* pointer to drone battery
     */
    Battery* GetBattery();
    /**
     * @brief Destroy the Drone object and its dynamically allocated battery
     * 
     */
    ~Drone();

 private:
    Battery* battery;
    Package* package_;
    std::vector< std::vector<float> > path;
    int pathIndex;
    bool hasPackage;

    /**
     * @brief Pick up and move the package along with the drone.  
     * 
     * @details Sets the position and direction of the package to the drone's to match the movement. 
     */
    void CarryPackage();
    /**
     * @brief Sets the direction of the Drone to the given coordinate point
     * 
     * @details Overrides the SetDirection from the base class EntityBase. Takes in the new destination and checks
     * if drone is already at given destination. If so, the method does not change the drone's direction. Else, the direction is
     * calculated using Vector math: direction = destination - position. Finally, the direction is normalized before being set
     * as the drone's new direction for movement. 
     * 
     * @param[in] destination vector with (x,y,z) float coordinates
     */
    void SetDirection(const std::vector<float>& dest) override;
};

}   // namespace csci3081

#endif   // DRONE_H
