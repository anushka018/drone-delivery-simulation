#include "path_strategy.h"

#ifndef PARABOLIC_PATH_H
#define PARABOLIC_PATH_H

namespace csci3081 {

class ParabolicPath : public PathStrategy {
    public:
        std::vector < std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph) override{
            std::vector < std::vector<float> > path = {};
            // initialize starting position and first destination to package
            float initialX = carrierPosition.at(0);
            float finalX = packagePosition.at(0);
            float initialY = carrierPosition.at(1);
            float finalY = packagePosition.at(1);
            float initialZ = carrierPosition.at(2);
            float finalZ = packagePosition.at(2);
            // Set height of jump (may need to adjust to avoid buildings)
            float height = 1.0;
            // Create path from carrier to package
            float x = 0.0, y = 0.0, z = 0.0;
            for (int i = 0; i <= 100; i++) {
                float dt = ((float) i) / 101;
                x = initialX + (finalX - initialX)*dt;
                z = initialZ + (finalZ - initialZ)*dt;
                y = ((4*height)+(-2*initialY)+(-2*finalY))*dt*dt + ((-4*height)+(3*initialY) + finalY)*dt + initialY;
                std::vector<float> position = {x,y,z};
                path.push_back(position);
            }
            // Reset to create jump from package to customer
            initialX = finalX;
            initialY = finalY;
            initialZ = finalZ;
            finalX = customerPosition.at(0);
            finalY = customerPosition.at(1);
            finalZ = customerPosition.at(2);
            // Create path from package to customer
            for (int i = 0; i <= 100; i++) {
                float dt = ((float) i) / 100;
                x = initialX + (finalX - initialX)*dt;
                z = initialZ + (finalZ - initialZ)*dt;
                y = ((4*height)+(-2*initialY)+(-2*finalY))*dt*dt + ((-4*height)+(3*initialY) + finalY)*dt + initialY;
                std::vector<float> position = {x,y,z};
                path.push_back(position);
            }
            path.push_back(customerPosition);
            return path;
        }                           
};

}
#endif // PARABOLIC_PATH_H