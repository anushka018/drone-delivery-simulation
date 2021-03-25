/**
 * @file battery.h
 * @author Audrey Kelly
 */
#ifndef BATTERY_H
#define BATTERY_H

namespace csci3081 {
/**
 * @brief Battery Class to provide power to drones, trucks, and robots
 * 
 */
class Battery {
 public:
    /**
     * @brief Construct a new Battery object. Default charge is 10000 seconds.
     * 
     * @param[in] charge to initialize the battery life
     */
    Battery(float charge = 10000);
    /**
    * @brief Get the maximum charge of the battery object in seconds
    * 
    * @return Maximum life of the battery in seconds
    */
    float GetMaxCharge();
    /**
     * @brief Get the battery reserve in seconds 
     * 
     * @return Remaining battery life in seconds
     */
    float GetBatteryReserve();
    /**
     * @brief Checks if the battery has any life remaining
     * 
     * @return true if the battery has zero charge
     * @return false if the battery has life remaining
     */
    bool IsDead();
    /**
     * @brief Increase charge in battery by units of seconds
     * 
     * @param[in] charge: seconds of charge to add to battery life 
     */
    void IncreaseCharge(float charge);
    /**
     * @brief Decrease charge in battery by units of seconds
     * 
     * @param[in] charge: seconds of charge to subtract from battery life 
     */
    void DecreaseCharge(float charge);

 private:
    float maxCharge;
    float batteryReserve;
    bool noChargeLeft;
    };

} //    namespace csci3081

#endif //   BATTERY_H