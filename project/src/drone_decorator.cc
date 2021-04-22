/**
 * @file drone_decorator.cc
 */
#include "drone_decorator.h"
#include "picojson.h"

namespace csci3081 { 

DroneDecorator::DroneDecorator(Drone* drone) {
    drone_ = drone;
};

void DroneDecorator::Update(float dt) {
    drone_ ->Update(dt);
};

}