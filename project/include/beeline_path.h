#include "path_strategy.h"

#ifndef BEELINE_PATH_H
#define BEELINE_PATH_H

namespace csci3081 {

class BeelinePath : public PathStrategy {
    public:
        std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) override {

        std::vector< std::vector<float> > path;

    
        std::vector<float> carrierPositionCopy = carrierPosition;
        carrierPositionCopy.at(1) = 400; 
        path.push_back(carrierPositionCopy);


        std::vector<float> packagePositionCopy = packagePosition;
        packagePositionCopy.at(1) = 400; 
        path.push_back(packagePositionCopy);


        path.push_back(packagePosition);
        path.push_back(packagePositionCopy);

        std::vector<float> customerPositionCopy = customerPosition;
        customerPositionCopy.at(1) = 400;
        path.push_back(customerPositionCopy);
        path.push_back(customerPosition);

		// 2 steps to get package to customer: 1. Get drone to package, 2. Get drone and package to customer
/* 
		Vector3D carrier_pos =  Vector3D(carrierPosition);
		Vector3D package_pos = Vector3D(packagePosition);
		Vector3D customer_pos = Vector3D(customerPosition);

		float drone_speed = drone-> GetSpeed(); //is there a way to get the speec of drone for createPath? 

		Vector3D package_direction = package_pos - carrier_pos;
		Vector3D customer_distance = customer_pos - carrier_pos;




		// 1. Drone to package
		// while loop checks if the length (magnitude) of package_direction vector is greater than the package radius. 
		// If not, this means drone is in range of package to be picked up 

		while (package_direction.GetMagnitude() > package -> GetRadius()){    //is there a way to get the radius of a package for createPath? 

			std::cout <<"Check 1"<<std::endl;
			std::cout <<"Magnitude "<<package_direction.Magnitude()<<" Radius "<< package ->GetRadius();

			// Move the drone towards package
			Vector3D unit_package_direction = package_direction.Unit_vector();
			Vector3D drone_velocity = unit_package_direction.Scalar_mul(drone_speed); 
			
			Vector3D drone_position_update = drone_velocity.Scalar_mul(dt); //v(dt)
			
			Vector3D drone_final_position = carrier_pos + drone_position_update; //z = zo + v(dt)
			path.push_back(drone_final_position.GetVector()) //add this to the path 

		}

		path.pop_back();// to remove duplicate coordinate

		
		// 2. Get (Drone, Package) to Customer
		while (customer_distance.Magnitude() > customer -> GetRadius()){ //is there a way to get the radius of a package for createPath? 

			// Move the drone towards package
			Vector3D unit_customer_direction = customer_distance.Unit_vector();
			Vector3D drone_to_customer_velocity = unit_customer_direction.Scalar_mul(drone_speed);
			
			Vector3D drone_to_customer_position_update = drone_to_customer_velocity.Scalar_mul(dt);
			
			Vector3D drone_to_customer_final_position = drone_pos + drone_to_customer_position_update; 
			Vector3D package_to_customer_final_position = package_pos + drone_to_customer_position_update;

			path.push_back(drone_to_customer_final_position.GetVector());


			//drone -> SetPosition(drone_to_customer_final_position.ConvertIntoVector());
			//package -> SetPosition(package_to_customer_final_position.ConvertIntoVector());
		} */

		return path;

	}
                                               
};

}
#endif // BEELINE_PATH_H