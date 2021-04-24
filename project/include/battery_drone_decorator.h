 /*
 * @file base_drone_decorator.h
 */
#ifndef BATTERY_DRONE_DECORATOR_H
#define BATTERY_DRONE_DECORATOR_H

#include "base_drone_decorator.h"
#include "drone.h"

namespace csci3081 {
/**
 * @brief Battery Drone Decorator Class
 * 
 */
class BatteryDroneDecorator : public BaseDroneDecorator { 
    public:
        BatteryDroneDecorator(PackageCarrier* drone);

        void Update(float dt) override;
    
};
}

#endif