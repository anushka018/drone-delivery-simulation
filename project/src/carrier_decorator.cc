/**
 * @file decorated_drone.cc
 */
#include "carrier_decorator.h"
#include "picojson.h"

namespace csci3081 { 

CarrierDecorator::CarrierDecorator(PackageCarrier* carrier): carrier_(carrier) {
};

}