#include "path_strategy.h"

#ifndef BEELINE_PATH_H
#define BEELINE_PATH_H

namespace csci3081 {

class BeelinePath : public PathStrategy {
    public:
        std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) override {
        /**
        std::vector< std::vector<float> > path;
	    path = graph_->GetPath(carrierPosition, packagePosition);
        // remove duplicate package position in middle of path
        path.pop_back();
	    std::vector< std::vector<float> > pathToCustomer = graph_->GetPath(packagePosition, customerPosition);
        // Merge two paths to form complete path from drone to customer
	    path.insert(path.end(), pathToCustomer.begin(), pathToCustomer.end());
        return path;
        **/
        }
                                                
};

}
#endif // BEELINE_PATH_H