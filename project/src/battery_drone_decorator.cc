/**
 * @file battery_drone_decorator.cc
 */
#include "battery_drone_decorator.h"
#include "picojson.h"
#include "json_helper.h"
#include <vector>
#include <string>

namespace csci3081 { 

BatteryDroneDecorator::BatteryDroneDecorator(PackageCarrier* drone) : BaseDroneDecorator(drone) {};

void BatteryDroneDecorator::Update(float dt) {
    drone_ ->Update(dt);
    // Change color of drone based on battery life
    float batteryLife = drone_->GetBattery()->GetBatteryReserve();
    float capacity = drone_->GetBattery()->GetMaxCharge();
    picojson::object& modified = const_cast<picojson::object&>(drone_->GetDetails());
    std::string currentColor;
    bool colorChanged = false;
    if (JsonHelper::ContainsKey(modified, "color")) {
        currentColor = JsonHelper::GetString(modified, "color");
    }
    if (batteryLife >= 0 && batteryLife <= (capacity / 6.0)) {
        if (currentColor.compare("0x8a2703") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0x8a2703");
            colorChanged = true;
        }
    }
    else if (batteryLife > (capacity / 6.0) && batteryLife <= (2.0 * capacity / 6.0)) {
        if (currentColor.compare("0xff5a1f") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0xff5a1f");
            colorChanged = true;
        }
    }
    else if (batteryLife > (2.0 * capacity / 6.0) && batteryLife <= (3.0 * capacity / 6.0)) {
        if (currentColor.compare("0xffc01f") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0xffc01f");
            colorChanged = true;
        }
    }
    else if (batteryLife > (3.0 * capacity / 6.0) && batteryLife <= (4.0 * capacity / 6.0)) {
        if (currentColor.compare("0xfff229") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0xfff229");
            colorChanged = true;
        }
    }
    else if (batteryLife > (4.0 * capacity / 6.0) && batteryLife <= (5.0 * capacity / 6.0)) {
        if (currentColor.compare("0x39ffa7") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0x39ffa7");
            colorChanged = true;
        }
    }
    else if (batteryLife > (5.0 * capacity / 6.0) && batteryLife <= capacity) {
        if (currentColor.compare("0x02bf17") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0x02bf17");
            colorChanged = true;
        }
    }
    if (colorChanged) {
        picojson::object eventObj = JsonHelper::CreateJsonNotification();
        JsonHelper::AddStringToJsonObject(eventObj, "value", "updateDetails");
        JsonHelper::AddObjectToJsonObject(eventObj, "details", modified);
        picojson::value notification = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
        Notify(notification, *this);
    }
}

}