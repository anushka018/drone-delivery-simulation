/**
 * @file delivery_scheduler.cc
 * @author Audrey Kelly
 */
#include "delivery_scheduler.h"

namespace csci3081 {
    DeliveryScheduler::DeliveryScheduler(const IGraph* graph) {
        graph_ = graph;
        nextCarrier = 0;
    }

    void DeliveryScheduler::ScheduleDelivery(Package* package, std::vector<PackageCarrier*> carriers, Customer* customer) {
        std::vector<float> customerLocation = customer->GetPosition();
	    package->SetDestination(customerLocation);
	    package->SetCustomer(customer);
        // If package is already at Customer's destination, the delivery should not be scheduled
        if (package->GetDestination().GetDistance(Vector3D(package->GetPosition())) <= package->GetRadius()) {
		    return;
	    }
        PackageCarrier* carrier = FindClosestCarrier(Vector3D(package->GetPosition()), carriers);
        if (carrier) {
            // Create path from drone/robot to package to customer
            std::vector< std::vector<float> > carrierPath = carrier->CreatePath(carrier->GetPosition(), package->GetPosition(), 
                                                                 customerLocation, graph_);                                                                                      
		    carrier->SetPath(carrierPath); 
		    carrier->AssignPackage(package);
        }
        else {
            // If there are no available drones/robots, then the delivery is stacked to the last carrier to be scheduled
            nextCarrier = nextCarrier % carriers.size();
            carrier = carriers.at(nextCarrier++);
            StackDeliveries(carrier, customer, package);
        }
        return;
    }

    PackageCarrier* DeliveryScheduler::FindClosestCarrier(const Vector3D packagePosition, std::vector<PackageCarrier*> carriers) {
        float minDistance = 1000000;
        float distanceToPackage = 0;
        Vector3D carrierPosition;
        PackageCarrier* closestCarrier = nullptr;
        for (PackageCarrier* carrier : carriers) {
            carrierPosition = Vector3D(carrier->GetPosition());
            distanceToPackage = carrierPosition.GetDistance(packagePosition);
            if (distanceToPackage < minDistance && !(carrier->IsDynamic())) {
                minDistance = distanceToPackage;
                closestCarrier = carrier;
            }
        }
        return closestCarrier;
    }

    void DeliveryScheduler::StackDeliveries(PackageCarrier* carrier, Customer* customer, Package* package) {
        std::vector< std::vector<float> > currentPath = carrier->GetPath();
        std::vector< std::vector<float> > extendedPath = carrier->CreatePath(currentPath.back(),
                                                                    package->GetPosition(), customer->GetPosition(), graph_);
        currentPath.insert(currentPath.end(), extendedPath.begin(), extendedPath.end());
        carrier->SetPath(currentPath);
        carrier->AssignPackage(package);
        return;
    }

}   //  end namespace csci3081 

