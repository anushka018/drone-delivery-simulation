/**
 * @file delivery_scheduler.h
 * @author Audrey Kelly
 */
#ifndef DELIVERY_SCHEDULER_H
#define DELIVERY_SCHEDULER_H

#include <EntityProject/facade/delivery_system.h>
#include "vector3D.h"
#include "drone.h"
#include "customer.h"
#include "package.h"

namespace csci3081 {
/**
 * @brief Delivery Scheduler sets up a delivery between a drone, package, and customer. 
 * 
 * @details The class assigns the package to a specific customer as well as assigns a drone to complete the delivery. 
 * The class also calculates the complete path for the drone to follow to pick up the package then deliver to the customer. 
 * 
 */
class DeliveryScheduler {
 public:
    /**
     * @brief Construct a new Delivery Scheduler object and set the IGraph* reference
     * 
     * @param[in] graph: IGraph* pointer to the graph of the delivery scene
     */
    DeliveryScheduler(const IGraph* graph);
    /**
     * @brief Establishes the necessary relationships and attributes of the entities to set-up and complete the delivery.
     * 
     * @details Calls CreatePath on the package carrier objects, using the strategy pattern to create different routes depending on the object's strategy.
     * 
     * @param[in] package: the Package entity to be delivered
     * @param[in] carriers: list of available Drones and Robots not currently delivering packages
     * @param[in] customer: the Customer entity receiving the package
     */
    void ScheduleDelivery(Package* package, std::vector<PackageCarrier*> carriers, Customer* customer);
 private:
   /**
    * @brief Reference to IGraph for creating smart routes on the proper web scene
    * 
    */
    const IGraph* graph_;
    /**
     * @brief This integer index is used for even delivery distribution between the carriers if there are multiple deliveries
     */
    int nextCarrier;
    /**
     * @brief Find the closest Drone or Robot to the package for schedule delivery method
     * 
     * @param[in] packagePosition: Vector3D to represent the package's coordinates in simulation
     * @param[in] carriers: list of available Drones and Robots not currently delivering packages
     * @return PackageCarrier*: the drone or robot available for the delivery
     */
    PackageCarrier* FindClosestCarrier(const Vector3D packagePosition, std::vector<PackageCarrier*> carriers);
    /**
     * @brief Assign a currently busy drone or robot to deliver another package in the future
     * 
     * @details Extends the package carrier's path from its current customer to the new package and then its assigned customer
     * 
     * @param[in] PackageCarrier* carrier for the package
     * @param[in] Customer* customer receiving package
     * @param[in] Package* package for delivery
     */
    void StackDeliveries(PackageCarrier* carrier, Customer* customer, Package* package);
};

} //    namespace csci3081

#endif //   DELIVERY_SCHEDULER_H