 /*
 * @file base_drone_decorator.h
 */
#ifndef BATTERY_DRONE_DECORATOR_H
#define BATTERY_DRONE_DECORATOR_H

#include "base_drone_decorator.h"
#include "drone.h"

namespace csci3081 {
/**
 * @brief Battery Drone Decorator Class. Changes the color of the sphere around the drone based on its battery life. Green means the battery is
 * well-charged, red means the battery is close to dying. 
 * 
 */
class BatteryDroneDecorator : public BaseDroneDecorator { 
    public:
        /**
         * @brief Construct a new Battery Drone Decorator object
         * 
         * @param[in] drone
         */
        BatteryDroneDecorator(PackageCarrier* drone);
        /**
         * @brief Update the drone and decorate it by adding color based on its battery life
         * 
         * @param[in] dt time step in seconds
         */
        void Update(float dt) override;
};
}

#endif