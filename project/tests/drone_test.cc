#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"

namespace csci3081 {
    class DroneTest : public ::testing::Test {
        public:
            void SetUp() {
                position = {0,0,0};
                direction = {1,0,0};
                droneObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(droneObj, "type", "drone");
                JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "direction", direction);

                packageObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(packageObj, "type", "package");
                JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "direction", direction);

                path = {{10,0,0},{10.5,10.6,10.3},{204.5,-4.32,-457},{0,0,0}};
            }
            void TearDown() {};

        protected:
            picojson::object droneObj;
            picojson::object packageObj;
            std::vector<float> position;
            std::vector<float> direction;
            std::vector< std::vector<float> > path;
    };

    TEST_F(DroneTest, DefaultConstructor) {
        // Constructor uses default values for name, weight, speed, radius
        Drone drone = Drone(position, direction, droneObj);
        ASSERT_EQ(picojson::value(drone.GetDetails()).serialize(), picojson::value(droneObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(drone.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(drone.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(drone.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(drone.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(drone.GetId(), drone.GetEntityCount());
        EXPECT_EQ(drone.GetVersion(), 0);
        EXPECT_FLOAT_EQ(drone.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(drone.GetSpeed(), 0.0);
        EXPECT_EQ((drone.GetName()), "Default Drone");
        EXPECT_EQ(drone.GetType(), "drone");
        EXPECT_EQ((drone.IsDynamic()), false);

        // Attributes initialized by Drone Constructor 
        EXPECT_TRUE(drone.GetBattery() != nullptr);
        EXPECT_EQ(drone.GetPath().size(), 0);
    }

    TEST_F(DroneTest, ValuedConstructor) {
        position = {10,-10,10};
        direction = {-25,30,45};
        // Constructor uses no default values
        Drone spidey = Drone(position, direction, droneObj, "Spiderman", 22.3, 0.6);
        ASSERT_EQ(picojson::value(spidey.GetDetails()).serialize(), picojson::value(droneObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(spidey.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(spidey.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(spidey.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(spidey.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(spidey.GetId(), spidey.GetEntityCount());
        EXPECT_EQ(spidey.GetVersion(), 0);
        EXPECT_FLOAT_EQ(spidey.GetRadius(), 0.6);
        EXPECT_FLOAT_EQ(spidey.GetSpeed(), 22.3);
        EXPECT_EQ((spidey.GetName()), "Spiderman");
        EXPECT_EQ(spidey.GetType(), "drone");
        EXPECT_EQ((spidey.IsDynamic()), false);

        // Attributes initialized by Drone Constructor 
        EXPECT_TRUE(spidey.GetBattery() != nullptr);
        EXPECT_EQ(spidey.GetPath().size(), 0);

        position = {1000000,0,43};
        direction = {-25,30,45};
        // Constructor uses default value for radius
        Drone ufo = Drone(position, direction, droneObj, "UFO", +3e8);
        ASSERT_EQ(picojson::value(ufo.GetDetails()).serialize(), picojson::value(droneObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(ufo.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(ufo.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(ufo.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(ufo.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(ufo.GetId(), ufo.GetEntityCount());
        EXPECT_EQ(ufo.GetVersion(), 0);
        EXPECT_FLOAT_EQ(ufo.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(ufo.GetSpeed(), +3e8);
        EXPECT_EQ((ufo.GetName()), "UFO");
        EXPECT_EQ(ufo.GetType(), "drone");
        EXPECT_EQ((ufo.IsDynamic()), false);

        // Attributes initialized by Drone Constructor 
        EXPECT_TRUE(ufo.GetBattery() != nullptr);
        EXPECT_EQ(ufo.GetPath().size(), 0);

        position = {200.45,12,-0.5};
        direction = {0,-1,0};
        // Constructor uses default value for radius and speed
        Drone drone = Drone(position, direction, droneObj, "kid with annoying drone");
        ASSERT_EQ(picojson::value(drone.GetDetails()).serialize(), picojson::value(droneObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(drone.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(drone.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(drone.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(drone.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(drone.GetId(), drone.GetEntityCount());
        EXPECT_EQ(drone.GetVersion(), 0);
        EXPECT_FLOAT_EQ(drone.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(drone.GetSpeed(), 0.0);
        EXPECT_EQ((drone.GetName()), "kid with annoying drone");
        EXPECT_EQ(drone.GetType(), "drone");
        EXPECT_EQ((drone.IsDynamic()), false);

        // Attributes initialized by Drone Constructor 
        EXPECT_TRUE(drone.GetBattery() != nullptr);
        EXPECT_EQ(drone.GetPath().size(), 0);
    }

    TEST_F(DroneTest, SetPosition) {
        Drone drone = Drone(position, direction, droneObj);
        ASSERT_EQ(drone.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), position.at(i));
        }

        std::vector<float> newPos = {1,1,1};
        drone.SetPosition(newPos);
        ASSERT_EQ(drone.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }

        newPos = {10,20,30};
        drone.SetPosition(newPos);
        ASSERT_EQ(drone.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }

        newPos = {1000000,2000,3.234};
        drone.SetPosition(newPos);
        ASSERT_EQ(drone.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }

        newPos = {-10.5,-0.137,3.234};
        drone.SetPosition(newPos);
        ASSERT_EQ(drone.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }

        newPos = {-10000,-2000000,-4760};
        drone.SetPosition(newPos);
        ASSERT_EQ(drone.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
    }
    
    // Update Test Part 1: Check how drone movement affects position and direction
    // as it moves along the given path
    TEST_F(DroneTest, UpdatePositionTest) {
        Drone drone = Drone(position, direction, droneObj);
        drone.SetPath(path);
        Package* package = new Package(position, direction, packageObj);
        drone.AssignPackage(package);

        ASSERT_EQ(position.size(), drone.GetPosition().size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(drone.GetPosition().at(i), position.at(i));
        }
        ASSERT_EQ(direction.size(), drone.GetDirection().size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(drone.GetDirection().at(i), direction.at(i));
        }

        // Both speed and dt are set to zero
        drone.SetPath(path);
        drone.SetSpeed(0.0);
        float dt = 0;
        drone.Update(dt);
        std::vector<float> newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        
        // Speed is zero, dt is nonzero
        dt = 0.10; 
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }

        // Speed is 1.0 and dt is 0.10
        // Current position is (0,0,0) and current direction is (1,0,0)
        drone.SetSpeed(1.0);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_FLOAT_EQ(newPos.at(0), 0.10);
        EXPECT_FLOAT_EQ(newPos.at(1), 0);
        EXPECT_FLOAT_EQ(newPos.at(2), 0);

        // Speed is 10.0 and dt is 0.10
        // Current position is (0.1,0,0) and current direction is (1,0,0)
        drone.SetSpeed(10.0);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 1.1, 0.001);
        EXPECT_NEAR(newPos.at(1), 0, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);

        // Speed is 10.0 and dt is 0.5
        // Current position is (1.1,0,0) and current direction is (1,0,0)
        drone.SetSpeed(20.0);
        dt = 0.4;
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_FLOAT_EQ(newPos.at(0), 9.1);
        EXPECT_FLOAT_EQ(newPos.at(1), 0);
        EXPECT_FLOAT_EQ(newPos.at(2), 0);
        // Drone is now near the first point in path, should switch direction
        dt = 0.10;
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 11.1, 0.001);
        EXPECT_NEAR(newPos.at(1), 0, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), 1, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0, 0.001);

        // Update towards point 2 in path {10.5,10.6,10.3}
        drone.Update(dt);
        drone.Update(dt);
        drone.Update(dt);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 10.776, 0.001);
        EXPECT_NEAR(newPos.at(1), 5.733, 0.001);
        EXPECT_NEAR(newPos.at(2), 5.570, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), -0.041, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0.717, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0.696, 0.001);
        
        // Reach point 2
        drone.Update(dt);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 10.613, 0.001);
        EXPECT_NEAR(newPos.at(1), 8.599, 0.001);
        EXPECT_NEAR(newPos.at(2), 8.356, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), -0.041, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0.717, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0.696, 0.001);

        // Drone switches destination to point 3 {204.5,-4.32,-457}
        // Direction should now be negative
        drone.SetSpeed(100.0);
        drone.Update(dt);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 10.613, 0.001);
        EXPECT_NEAR(newPos.at(1), 8.599, 0.001);
        EXPECT_NEAR(newPos.at(2), 8.356, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), 0.041, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), -0.717, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), -0.696, 0.001);

        // Overshoot point 2; speed is too high and dt too large
        for (int j = 0; j < 22; j++) {
            drone.Update(dt);
        }
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 10.208, 0.001);
        EXPECT_NEAR(newPos.at(1), 15.765, 0.001);
        EXPECT_NEAR(newPos.at(2), 15.319, 0.001);

        // move back towards point 2
        for (int j = 0; j < 24; j++) {
            drone.Update(dt);
        }
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 10.613, 0.001);
        EXPECT_NEAR(newPos.at(1), 8.599, 0.001);
        EXPECT_NEAR(newPos.at(2), 8.356, 0.001);

        drone.SetSpeed(10.0);
        // Return drone to origin
        dt = 0.10;
        while (drone.GetPosition().at(0) > 0.5) {
            drone.Update(dt);
        }
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 0, 0.5);
        EXPECT_NEAR(newPos.at(1), 0, 0.5);
        EXPECT_NEAR(newPos.at(2), 0, 0.5);
        
        delete package;

    }
    

    // Update Test Part 2: Check how drone movement affects the drone's battery charge
    TEST_F(DroneTest, UpdateBatteryDrain) {
        Drone drone = Drone(position, direction, droneObj);
        drone.SetPath(path);
        Package* package = new Package(position, direction, packageObj);
        drone.AssignPackage(package);
        ASSERT_EQ(drone.GetBattery()->GetMaxCharge(), 10000);
        ASSERT_EQ(drone.GetBattery()->GetBatteryReserve(), 10000);

        // Speed is 1.0 and dt is 0.10
        // Current position is (0,0,0) and current direction is (1,0,0)
        float dt = 0.10;
        drone.SetSpeed(1.0);
        drone.Update(dt);
        EXPECT_FLOAT_EQ(drone.GetBattery()->GetBatteryReserve(), 9999.9);
        
        dt = 0.5;
        drone.Update(dt);
        EXPECT_FLOAT_EQ(drone.GetBattery()->GetBatteryReserve(), 9999.4);

        dt = 1;
        drone.Update(dt);
        EXPECT_FLOAT_EQ(drone.GetBattery()->GetBatteryReserve(), 9998.4);

        dt = 100;
        drone.Update(dt);
        EXPECT_FLOAT_EQ(drone.GetBattery()->GetBatteryReserve(), 9898.4);

        path.push_back({1000000,2000000,3000000});
        dt = 9000;
        drone.Update(dt);
        EXPECT_NEAR(drone.GetBattery()->GetBatteryReserve(), 898.4, 0.01);

        dt = 1000;
        drone.Update(dt);
        EXPECT_FLOAT_EQ(drone.GetBattery()->GetBatteryReserve(), 0);

        // Drone should not Update if battery is dead
        dt = 1;
        std::vector<float> prevPos = drone.GetPosition();
        drone.Update(dt);
        std::vector<float> newPos = drone.GetPosition();
        EXPECT_FLOAT_EQ(drone.GetBattery()->GetBatteryReserve(), 0);
        ASSERT_EQ(prevPos.size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(prevPos.at(i), newPos.at(i));
        }

        delete package;
    }

   
    TEST_F(DroneTest, SetGetPath) {
        Drone drone = Drone(position, direction, droneObj);
        EXPECT_EQ(drone.GetPath().size(), 0);

        drone.SetPath(path);

        ASSERT_EQ(drone.GetPath().size(), path.size());
        for (int i = 0; i < path.size(); i++) {
            ASSERT_EQ(drone.GetPath().at(i).size(), path.at(i).size());
            for (int j = 0; j < path.at(i).size(); j++) {
                EXPECT_EQ(drone.GetPath().at(i).at(j), path.at(i).at(j));
            }
        }

        std::vector< std::vector<float> > newPath = {{0.9,0.8,6.5},{1,2,3},{9,5.3,-12.7},{4000,-8000,10000}};
        drone.SetPath(newPath);

        ASSERT_EQ(drone.GetPath().size(), newPath.size());
        for (int i = 0; i < newPath.size(); i++) {
            ASSERT_EQ(drone.GetPath().at(i).size(), newPath.at(i).size());
            for (int j = 0; j < newPath.at(i).size(); j++) {
                EXPECT_EQ(drone.GetPath().at(i).at(j), newPath.at(i).at(j));
            }
        }

        std::vector< std::vector<float> > newerPath(100, {0.5,0.6,0.1});
        drone.SetPath(newerPath);

        ASSERT_EQ(drone.GetPath().size(), newerPath.size());
        for (int i = 0; i < newerPath.size(); i++) {
            ASSERT_EQ(drone.GetPath().at(i).size(), newerPath.at(i).size());
            for (int j = 0; j < newerPath.at(i).size(); j++) {
                EXPECT_EQ(drone.GetPath().at(i).at(j), newerPath.at(i).at(j));
            }
        }
    }
}




