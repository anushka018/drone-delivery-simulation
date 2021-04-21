/**
 * @file decorated_drone.cc
 */
#include "carrier_decorator.h"
#include "picojson.h"

namespace csci3081 { 

CarrierDecorator::CarrierDecorator(PackageCarrier* carrier): carrier_(carrier) {};

void CarrierDecorator::Update(float dt) {
    carrier_->Update(dt);
}
// add more method definitions from package carrier and entity base here
}