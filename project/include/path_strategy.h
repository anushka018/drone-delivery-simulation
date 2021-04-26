#include <vector>
#include <EntityProject/graph.h>

#ifndef PATH_STRATEGY_H
#define PATH_STRATEGY_H

namespace csci3081 {

class PathStrategy {
    public:
        /**
         * @brief Create a Path for the path attribute of the drone or robot
         * 
         * @param[in] carrierPosition, float vector coordinate of the drone's origin
         * @param[in] packagePosition, float vector coordinate of the package
         * @param[in] customerPosition, float vector coordinate of the customer
         * @param[in] graph, an IGraph* pointer to the simulation map to use the GetPath method from the IGraph* class
         * @return std::vector < std::vector<float> > path for drone to follow in its update method
         */
        virtual std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph = nullptr) = 0;
};
}
#endif // PATH_STRATEGY_H