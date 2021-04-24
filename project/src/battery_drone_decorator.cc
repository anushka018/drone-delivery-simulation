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
    /**
    unsigned int intColor = rgb((capacity - batteryLife) / capacity);
    std::string color = std::to_string(intColor);
    JsonHelper::AddStringToJsonObject(modified, "color", color);
    **/
    if (batteryLife >= 0 && batteryLife <= 1666.67) {
        if (currentColor.compare("0x8a2703") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0x8a2703");
            colorChanged = true;
        }
    }
    else if (batteryLife > 1666.67 && batteryLife <= 3333.32) {
        if (currentColor.compare("0xff5a1f") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0xff5a1f");
            colorChanged = true;
        }
    }
    else if (batteryLife > 3333.32 && batteryLife <= 4999.98) {
        if (currentColor.compare("0xffc01f") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0xffc01f");
            colorChanged = true;
        }
    }
    else if (batteryLife > 4999.98 && batteryLife <= 6666.64) {
        if (currentColor.compare("0xfff229") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0xfff229");
            colorChanged = true;
        }
    }
    else if (batteryLife > 6666.64 && batteryLife <= 8333.3) {
        if (currentColor.compare("0x39ffa7") != 0) {
            JsonHelper::AddStringToJsonObject(modified, "color","0x39ffa7");
            colorChanged = true;
        }
    }
    else if (batteryLife > 8333.3 && batteryLife <= 10000) {
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
/**
    //input: ratio is between 0 to 1
    //output: rgb color
    unsigned int BatteryDroneDecorator::rgb(double ratio) {
        //we want to normalize ratio so that it fits in to 6 regions
        //where each region is 256 units long
        int normalized = int(ratio * 256 * 6);

        //find the distance to the start of the closest region
        int x = normalized % 256;
        int red = 0, grn = 0, blu = 0;
        switch(normalized / 256) {
            case 0: red = 255;      grn = x;        blu = 0;       break; //red
            case 1: red = 255 - x;  grn = 255;      blu = 0;       break; //yellow
            case 2: red = 0;        grn = 255;      blu = x;       break; //green
            case 3: red = 0;        grn = 255 - x;  blu = 255;     break; //cyan
            case 4: red = x;        grn = 0;        blu = 255;     break; //blue
            case 5: red = 255;      grn = 0;        blu = 255 - x; break; //magenta
        }
        return red + (grn << 8) + (blu << 16);
    }

}
**/
}