#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "Robot.h"

namespace csci3081 {
    class RobotTest : public ::testing::Test {
        public:
            void SetUp() {
                position = {0,0,0};
                direction = {1,0,0};
                robotObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(robotObj, "type", "Robot");
                JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "direction", direction);

                packageObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(packageObj, "type", "package");
                JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "direction", direction);

                path = {{2,0,0},{0,2,0},{5,4,3},{0,0,0}};
            }
            void TearDown() {};

        protected:
            picojson::object robotObj;
            picojson::object packageObj;
            std::vector<float> position;
            std::vector<float> direction;
            std::vector< std::vector<float> > path;
    };

    TEST_F(RobotTest, DefaultConstructor) {
        // Constructor uses default values for name, weight, speed, radius
        Robot robot = Robot(position, direction, robotObj);
        ASSERT_EQ(picojson::value(robot.GetDetails()).serialize(), picojson::value(robotObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(robot.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(robot.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(robot.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(robot.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(robot.GetId(), robot.GetEntityCount());
        EXPECT_EQ(robot.GetVersion(), 0);
        EXPECT_FLOAT_EQ(robot.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(robot.GetSpeed(), 0.0);
        EXPECT_EQ((robot.GetName()), "Default robot");
        EXPECT_EQ(robot.GetType(), "robot");
        EXPECT_EQ((robot.IsDynamic()), false);

        // Attributes initialized by Robot Constructor 
        EXPECT_TRUE(robot.GetBattery() != nullptr);
        EXPECT_EQ(robot.GetPath().size(), 0);
    }

    TEST_F(RobotTest, ValuedConstructor) {
        position = {10,-10,10};
        direction = {-25,30,45};
        // Constructor uses no default values
        Robot spidey = Robot(position, direction, robotObj, "Spiderman", 22.3, 0.6);
        ASSERT_EQ(picojson::value(spidey.GetDetails()).serialize(), picojson::value(robotObj).serialize());
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
        EXPECT_EQ(spidey.GetType(), "robot");
        EXPECT_EQ((spidey.IsDynamic()), false);

        // Attributes initialized by Robot Constructor 
        EXPECT_TRUE(spidey.GetBattery() != nullptr);
        EXPECT_EQ(spidey.GetPath().size(), 0);

        position = {1000000,0,43};
        direction = {-25,30,45};
        // Constructor uses default value for radius
        Robot ufo = Robot(position, direction, robotObj, "UFO", +3e8);
        ASSERT_EQ(picojson::value(ufo.GetDetails()).serialize(), picojson::value(robotObj).serialize());
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
        EXPECT_EQ(ufo.GetType(), "robot");
        EXPECT_EQ((ufo.IsDynamic()), false);

        // Attributes initialized by Robot Constructor 
        EXPECT_TRUE(ufo.GetBattery() != nullptr);
        EXPECT_EQ(ufo.GetPath().size(), 0);

        position = {200.45,12,-0.5};
        direction = {0,-1,0};
        // Constructor uses default value for radius and speed
        Robot robot = Robot(position, direction, robotObj, "annoying Robot");
        ASSERT_EQ(picojson::value(robot.GetDetails()).serialize(), picojson::value(robotObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(robot.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(robot.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(robot.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(robot.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(robot.GetId(), robot.GetEntityCount());
        EXPECT_EQ(robot.GetVersion(), 0);
        EXPECT_FLOAT_EQ(robot.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(robot.GetSpeed(), 0.0);
        EXPECT_EQ((robot.GetName()), "annoying Robot");
        EXPECT_EQ(robot.GetType(), "robot");
        EXPECT_EQ((robot.IsDynamic()), false);

        // Attributes initialized by Robot Constructor 
        EXPECT_TRUE(robot.GetBattery() != nullptr);
        EXPECT_EQ(robot.GetPath().size(), 0);
    }

    TEST_F(RobotTest, SetPosition) {
        Robot robot = Robot(position, direction, robotObj);
        ASSERT_EQ(robot.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), position.at(i));
        }

        std::vector<float> newPos = {1,1,1};
        robot.SetPosition(newPos);
        ASSERT_EQ(robot.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }

        newPos = {10,20,30};
        robot.SetPosition(newPos);
        ASSERT_EQ(robot.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }

        newPos = {1000000,2000,3.234};
        robot.SetPosition(newPos);
        ASSERT_EQ(robot.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }

        newPos = {-10.5,-0.137,3.234};
        robot.SetPosition(newPos);
        ASSERT_EQ(robot.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }

        newPos = {-10000,-2000000,-4760};
        robot.SetPosition(newPos);
        ASSERT_EQ(robot.GetPosition().size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
    }

    // Update Test Part 1: Check how Robot movement affects position and direction
    // as it moves along the given path
    TEST_F(RobotTest, UpdatePositionTest) {
        Robot robot = Robot(position, direction, robotObj);
        robot.SetPath(path);
        Package* package = new Package(position, direction, packageObj);
        robot.AssignPackage(package);
        ASSERT_EQ(position.size(), robot.GetPosition().size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(robot.GetPosition().at(i), position.at(i));
        }
        ASSERT_EQ(direction.size(), robot.GetDirection().size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(robot.GetDirection().at(i), direction.at(i));
        }

        // Both speed and dt are set to zero
        robot.SetSpeed(0.0);
        float dt = 0;
        robot.Update(dt);
        std::vector<float> newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        
        // Speed is zero, dt is nonzero
        dt = 0.10; 
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }

        // Speed is 1.0 and dt is 0.10
        // Current position is (0,0,0) and current direction is (1,0,0)
        robot.SetSpeed(1.0);
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_FLOAT_EQ(newPos.at(0), 0.10);
        EXPECT_FLOAT_EQ(newPos.at(1), 0);
        EXPECT_FLOAT_EQ(newPos.at(2), 0);

        // Speed is 10.0 and dt is 0.10
        // Current position is (0.1,0,0) and current direction is (1,0,0)
        robot.SetSpeed(10.0);
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 1.1, 0.001);
        EXPECT_NEAR(newPos.at(1), 0, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);

        // Speed is 10.0 and dt is 0.10
        // Robot has reached (1.1,0,0) and is now headed to (2,0,0)
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 2.1, 0.001);
        EXPECT_NEAR(newPos.at(1), 0, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);

        // Robot has reached (2,0,0) and is now headed to (0,2,0)
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 1.376, 0.001);
        EXPECT_NEAR(newPos.at(1), 0.689, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(0), -0.724, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(1), 0.690, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(2), 0, 0.001);

        robot.Update(dt);
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), -0.072, 0.001);
        EXPECT_NEAR(newPos.at(1), 2.069, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(0), -0.724, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(1), 0.690, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(2), 0, 0.001);
  
        // Robot has reached point 2, moving to (5,4,3)
        robot.Update(dt);
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 1.563, 0.001);
        EXPECT_NEAR(newPos.at(1), 2.692, 0.001);
        EXPECT_NEAR(newPos.at(2), 0.968, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(0), 0.817, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(1), 0.311, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(2), 0.484, 0.001);

        robot.Update(dt);
        robot.Update(dt);
        robot.Update(dt);
        robot.Update(dt);
        newPos = robot.GetPosition();
        ASSERT_EQ(newPos.size(), robot.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(robot.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 5.0, 0.5);
        EXPECT_NEAR(newPos.at(1), 4.0, 0.5);
        EXPECT_NEAR(newPos.at(2), 3.0, 0.5);
        EXPECT_NEAR(robot.GetDirection().at(0), 0.817, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(1), 0.311, 0.001);
        EXPECT_NEAR(robot.GetDirection().at(2), 0.484, 0.001);

        delete package;

    }

    // Update Test Part 2: Check how Robot movement affects the Robot's battery charge
    TEST_F(RobotTest, UpdateBatteryDrain) {
        Robot robot = Robot(position, direction, robotObj);
        robot.SetPath(path);
        Package* package = new Package(position, direction, packageObj);
        robot.AssignPackage(package);
        ASSERT_EQ(robot.GetBattery()->GetMaxCharge(), 10000);
        ASSERT_EQ(robot.GetBattery()->GetBatteryReserve(), 10000);

        // Speed is 1.0 and dt is 0.10
        // Current position is (0,0,0) and current direction is (1,0,0)
        float dt = 0.10;
        robot.SetSpeed(1.0);
        robot.Update(dt);
        EXPECT_FLOAT_EQ(robot.GetBattery()->GetBatteryReserve(), 9999.9);
        
        dt = 0.5;
        robot.Update(dt);
        EXPECT_FLOAT_EQ(robot.GetBattery()->GetBatteryReserve(), 9999.4);

        dt = 1;
        robot.Update(dt);
        EXPECT_FLOAT_EQ(robot.GetBattery()->GetBatteryReserve(), 9998.4);

        dt = 100;
        robot.Update(dt);
        EXPECT_FLOAT_EQ(robot.GetBattery()->GetBatteryReserve(), 9898.4);

        path.push_back({1000000,2000000,3000000});
        dt = 9000;
        robot.Update(dt);
        EXPECT_NEAR(robot.GetBattery()->GetBatteryReserve(), 898.4, 0.01);

        dt = 1000;
        robot.Update(dt);
        EXPECT_FLOAT_EQ(robot.GetBattery()->GetBatteryReserve(), 0);

        // Robot should not Update if battery is dead
        dt = 1;
        std::vector<float> prevPos = robot.GetPosition();
        robot.Update(dt);
        std::vector<float> newPos = robot.GetPosition();
        EXPECT_FLOAT_EQ(robot.GetBattery()->GetBatteryReserve(), 0);
        ASSERT_EQ(prevPos.size(), newPos.size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(prevPos.at(i), newPos.at(i));
        }

        delete package;
    }

   
    TEST_F(RobotTest, SetGetPath) {
        Robot robot = Robot(position, direction, robotObj);
        EXPECT_EQ(robot.GetPath().size(), 0);

        robot.SetPath(path);

        ASSERT_EQ(robot.GetPath().size(), path.size());
        for (int i = 0; i < path.size(); i++) {
            ASSERT_EQ(robot.GetPath().at(i).size(), path.at(i).size());
            for (int j = 0; j < path.at(i).size(); j++) {
                EXPECT_EQ(robot.GetPath().at(i).at(j), path.at(i).at(j));
            }
        }

        std::vector< std::vector<float> > newPath = {{0.9,0.8,6.5},{1,2,3},{9,5.3,-12.7},{4000,-8000,10000}};
        robot.SetPath(newPath);

        ASSERT_EQ(robot.GetPath().size(), newPath.size());
        for (int i = 0; i < newPath.size(); i++) {
            ASSERT_EQ(robot.GetPath().at(i).size(), newPath.at(i).size());
            for (int j = 0; j < newPath.at(i).size(); j++) {
                EXPECT_EQ(robot.GetPath().at(i).at(j), newPath.at(i).at(j));
            }
        }

        std::vector< std::vector<float> > newerPath(100, {0.5,0.6,0.1});
        robot.SetPath(newerPath);

        ASSERT_EQ(robot.GetPath().size(), newerPath.size());
        for (int i = 0; i < newerPath.size(); i++) {
            ASSERT_EQ(robot.GetPath().at(i).size(), newerPath.at(i).size());
            for (int j = 0; j < newerPath.at(i).size(); j++) {
                EXPECT_EQ(robot.GetPath().at(i).at(j), newerPath.at(i).at(j));
            }
        }
    }
}