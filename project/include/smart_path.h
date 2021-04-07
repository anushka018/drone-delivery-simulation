#include "path_strategy.h"

#ifndef SMART_PATH_H
#define SMART_PATH_H

namespace csci3081 {

class SmartPath : public PathStrategy {
    public:

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
        std::cout << "Path Size in smart path" << size << std::endl;
        return path;
    }                                     
};

}
#endif  // SMART_PATH_H