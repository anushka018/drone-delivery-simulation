/**
 * @file delivery_scheduler.cc
 * @author Audrey Kelly
 */
#include "delivery_scheduler.h"

namespace csci3081 {
    DeliveryScheduler::DeliveryScheduler(const IGraph* graph) {
        graph_ = graph;
    }

    void DeliveryScheduler::ScheduleDelivery(Package* package, PackageCarrier* carrier, Customer* customer) {
        std::vector<float> customerLocation = customer->GetPosition();
	    package->SetDestination(customerLocation);
	    package->SetCustomer(customer);
        // If package is already at Customer's destination, the delivery should not be scheduled
        if (package->GetDestination().GetDistance(Vector3D(package->GetPosition())) <= package->GetRadius()) {
		    return;
	    }
        // Create path from drone/robot to package to customer
        std::vector< std::vector<float> > carrierPath = CreatePath(carrier->GetPosition(), package->GetPosition(), customerLocation);
		carrier->SetPath(carrierPath);
		carrier->AssignPackage(package);
        return;
    }

    std::vector< std::vector<float> > DeliveryScheduler::CreatePath(std::vector<float> carrierPosition, 
																std::vector<float> packagePosition, std::vector<float> customerPosition) {
        std::vector< std::vector<float> > path;
	    path = graph_->GetPath(carrierPosition, packagePosition);
        // remove duplicate package position in middle of path
        path.pop_back();
	    std::vector< std::vector<float> > pathToCustomer = graph_->GetPath(packagePosition, customerPosition);
        // Merge two paths to form complete path from drone to customer
	    path.insert(path.end(), pathToCustomer.begin(), pathToCustomer.end());
        return path;
    }
}   //  end namespace csci3081

