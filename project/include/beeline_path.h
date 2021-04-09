#include "path_strategy.h"

#ifndef BEELINE_PATH_H
#define BEELINE_PATH_H

namespace csci3081 {

class BeelinePath : public PathStrategy {
    public:
        std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) override {

        std::vector< std::vector<float> > path;

		path.push_back(carrierPosition);
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
		return path;
	}
                                               
};

}
#endif // BEELINE_PATH_H