/**
 * @file battery.cc
 * @author Audrey Kelly
 */
#include "battery.h"

namespace csci3081 {

    Battery::Battery(float charge) {
        if (charge > 0) {
            maxCharge = charge;
            batteryReserve = charge;
            noChargeLeft = false;
        }
        else if (charge <= 0) { // charge cannot be negative
            maxCharge = 0;
            batteryReserve = 0;
            noChargeLeft = true;
        }
    }

    float Battery::GetMaxCharge() {
        return maxCharge;
    }

    float Battery::GetBatteryReserve() {
        return batteryReserve;
    }

    bool Battery::IsDead() {
        return noChargeLeft;
    }

    void Battery::IncreaseCharge(float charge) {
        batteryReserve += charge;
        if (batteryReserve > 0) {
            noChargeLeft = false;
            if (batteryReserve > maxCharge) {   // cannot charge battery beyond maximum charge
            batteryReserve = maxCharge;
            }
        }
        else {
            noChargeLeft = true;
            batteryReserve = 0;     // batteryReserve cannot be negative
        }
    }

    void Battery::DecreaseCharge(float charge) {
        batteryReserve -= charge;
        if (batteryReserve <= 0) {
            noChargeLeft = true;
            batteryReserve = 0; // batteryReserve cannot be negative
        }
        else if (batteryReserve > maxCharge) { 
            batteryReserve = maxCharge; // cannot charge battery beyond maximum charge
        }
    }

}   // namespace csci3081