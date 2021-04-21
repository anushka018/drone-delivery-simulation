/**
 * @file carrier_decorator.h
 */
#ifndef CARRIER_DECORATOR_H
#define CARRIER_DECORATOR_H

#include "package_carrier.h"

namespace csci3081 {
/**
 * @brief Abstract Decorator Class
 * 
 */
class CarrierDecorator : public PackageCarrier { 
    public:
        CarrierDecorator(PackageCarrier* carrier);
        void Update(float dt) override;
    protected:
        PackageCarrier* carrier_;
};

}

#endif // CARRIER_DECORATOR_H