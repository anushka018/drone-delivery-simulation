
#ifndef BEELINE_PATH_H
#define BEELINE_PATH_H

#include "path_strategy.h"

namespace csci3081 {
/**
 * @brief This class contains the Beeline route method used only on drones
 * 
 * @details Creates a path directly flying over buildings from the origin of the drone to the package to the customer. 
 * The height of the path is 400 units in the simulation which is above all buildings on the map.
 */
class BeelinePath : public PathStrategy {
    public:
        /**
         * @brief Create a Beeline Path for the path attribute of the drone
         * 
         * @param[in] carrierPosition, float vector coordinate of the drone's origin
         * @param[in] packagePosition, float vector coordinate of the package
         * @param[in] customerPosition, float vector coordinate of the customer
         * @param[in] graph, an IGraph* pointer to the simulation map. Not necessary for this implementation of CreatePath, the default value of null is used instead.
         * @return std::vector < std::vector<float> > path for drone to follow in its update method
         */
        std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) override {

        std::vector< std::vector<float> > path;
        // Start at carrier position and fly up to 400 units height
		path.push_back(carrierPosition);
        std::vector<float> carrierPositionCopy = carrierPosition;
        carrierPositionCopy.at(1) = 400; 
        path.push_back(carrierPositionCopy);
        // Move directly to package position at 400 units height, fly down to pick up package
        std::vector<float> packagePositionCopy = packagePosition;
        packagePositionCopy.at(1) = 400; 
        path.push_back(packagePositionCopy);
        path.push_back(packagePosition);
        path.push_back(packagePositionCopy); // fly back up to 400
        // Move to customer and return to customer height for package drop-off
        std::vector<float> customerPositionCopy = customerPosition;
        customerPositionCopy.at(1) = 400;
        path.push_back(customerPositionCopy);
        path.push_back(customerPosition);
		return path;
	}      
};
}
#endif // BEELINE_PATH_H