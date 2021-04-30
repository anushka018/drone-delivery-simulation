#include "path_strategy.h"

#ifndef SMART_PATH_H
#define SMART_PATH_H

namespace csci3081 {
/**
 * @brief This class contains the Smart Route method for both drones and robots.
 * 
 * @details Uses the IGraph* pointer to the simulation map to create two paths avoiding buildings and other obstacles in the map. Merges
 * these two paths (from carrier to package and from package to customer) to form a complete path for carrier object to follow.
 */
class SmartPath : public PathStrategy {
    public:
        /**
         * @brief Create a Smart Path for the path attribute of the drone or robot
         * 
         * @param[in] carrierPosition, float vector coordinate of the drone's origin
         * @param[in] packagePosition, float vector coordinate of the package
         * @param[in] customerPosition, float vector coordinate of the customer
         * @param[in] graph, an IGraph* pointer to the simulation map to use the GetPath method from the IGraph* class
         * @return std::vector < std::vector<float> > path for drone to follow in its update method
         */
        std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) override {
    
        std::vector< std::vector<float> > path;
	    path = graph->GetPath(carrierPosition, packagePosition);
        // remove duplicate package position in middle of path
        path.pop_back();
	    std::vector< std::vector<float> > pathToCustomer = graph->GetPath(packagePosition, customerPosition);
        // Merge two paths to form complete path from drone to customer
	    path.insert(path.end(), pathToCustomer.begin(), pathToCustomer.end());
        int size = path.size();
        return path;
    }                                     
};

}
#endif  // SMART_PATH_H