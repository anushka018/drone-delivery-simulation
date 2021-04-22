/**
 * @file drone_decorator.cc
 */
#include "drone_decorator.h"
#include "picojson.h"
#include "json_helper.h"
#include <vector>
#include <string>

namespace csci3081 { 

DroneDecorator::DroneDecorator(Drone* drone) {
    drone_ = drone;
};

void DroneDecorator::Update(float dt) {
    std::vector <std::string> colors = {"0x02bf17", "0x39ffA7", "0xfff229", "0xffc01F", "0xff5a1f", "0x8a2703"};
    drone_ ->Update(dt);
    // Change color of drone based on battery life
    float battery = drone_->GetBattery()->GetBatteryReserve();
    // std::cout << "Battery: " << battery << std::endl;
    picojson::object& modified = const_cast<picojson::object&>(drone_->GetDetails());
    if (battery >= 0 && battery <= 1666.67) {
        JsonHelper::AddStringToJsonObject(modified, "color","0x8a2703");
    }
    else if (battery > 1666.67 && battery <= 3333.32) {
        JsonHelper::AddStringToJsonObject(modified, "color","0xff5a1f");
    }
    else if (battery > 3333.32 && battery <= 4999.98) {
        JsonHelper::AddStringToJsonObject(modified, "color","0xffc01F");
    }
    else if (battery > 4999.98 && battery <= 6666.64) {
        JsonHelper::AddStringToJsonObject(modified, "color","0xfff229");
    }
    else if (battery > 6666.64 && battery <= 8333.3) {
        JsonHelper::AddStringToJsonObject(modified, "color","0x39ffa7");
    }
    else if (battery > 8333.3 && battery <= 10000) {
        JsonHelper::AddStringToJsonObject(modified, "color","0x02bf17");
    }
};

}