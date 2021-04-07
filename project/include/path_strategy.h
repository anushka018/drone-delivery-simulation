#include <vector>
#include <EntityProject/graph.h>

#ifndef PATH_STRATEGY_H
#define PATH_STRATEGY_H

namespace csci3081 {

class PathStrategy {
    public:
        virtual std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph = nullptr) = 0;
};
}
#endif // PATH_STRATEGY_H