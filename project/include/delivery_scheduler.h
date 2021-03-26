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
     * @details 
     * 
     * @param[in] package: the Package entity to be delivered
     * @param[in] carrier: Drone or Robot entity to complete delivery
     * @param[in] dest: the Customer entity receiving the package
     */
    void ScheduleDelivery(Package* package, PackageCarrier* carrier, Customer* customer);
    /**
     * @brief Create the path along a smart route from the drone/robot to package to customer. 
     *
     * @see IGraph class for GetPath() method
     * 
     * @param[in] carrierPosition in float vector with coordinate points
     * @param[in] packagePosition in float vector with coordinate points
     * @param[in] customerPosition in float vector with coordinate points
     * @return List of vector coordinate points for path from drone to customer
     */
    std::vector< std::vector<float> > CreatePath(std::vector<float> carrierPosition,
                                                std::vector<float> packagePosition, std::vector<float> customerPosition);
 private:
    const IGraph* graph_;
};

} //    namespace csci3081

#endif //   DELIVERY_SCHEDULER_H