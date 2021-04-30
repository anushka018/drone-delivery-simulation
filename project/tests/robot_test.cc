#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/osm_graph_parser.h>
#include <EntityProject/entity_console_logger.h>
#include <EntityProject/graph.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "Robot.h"

namespace csci3081 {
    class RobotTest : public ::testing::Test {
        public:
            void SetUp() {
                system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));

                position = {0,0,0};
                direction = {1,0,0};
                robotObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(robotObj, "type", "robot");
                JsonHelper::AddFloatToJsonObject(robotObj, "radius", 1.0);
                JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(robotObj, "direction", direction);

                packageObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(packageObj, "type", "package");
                JsonHelper::AddFloatToJsonObject(packageObj, "radius", 1.0);
                std::vector<float> packagePosition = {20,264,-15};
                JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "position", packagePosition);
                JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "direction", direction);

                customerObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(customerObj, "type", "customer");
                std::vector<float> customerPosition = {100,264,17};
                JsonHelper::AddStdFloatVectorToJsonObject(customerObj, "position", customerPosition);
                JsonHelper::AddStdFloatVectorToJsonObject(customerObj, "direction", direction);

                path = {{2,0,0},{0,2,0},{5,4,3},{0,0,0}};
            }
            void TearDown() {};

        protected:
            IDeliverySystem* system;
            picojson::object robotObj;
            picojson::object packageObj;
            picojson::object customerObj;
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
        delete package;
    }

    // Update Test Part 3: Check for the proper observer notifications during the simulation
    TEST_F(RobotTest, UpdateObservers) {
        // Create and set the graph
        if (system) {
            entity_project::OSMGraphParser parser;
            const IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
            system->SetGraph(graph);
        }

        entity_project::EntityConsoleLogger logger;
        system->AddObserver(&logger);
        
        IEntity* robotEntity = system->CreateEntity(robotObj);
        IEntity* packageEntity = system->CreateEntity(packageObj);
        IEntity* customerEntity = system->CreateEntity(customerObj);

        system->AddEntity(robotEntity);
        system->AddEntity(packageEntity);
        system->AddEntity(customerEntity);
        Robot* robot = dynamic_cast<Robot*>(robotEntity);
        robot->SetSpeed(30.0);
        Package* package = dynamic_cast<Package*>(packageEntity);
        float dt = 0.01;

        // Check if observer is notified that package is scheduled
        testing::internal::CaptureStdout();
        system->ScheduleDelivery(packageEntity, customerEntity);
        std::string output1 = testing::internal::GetCapturedStdout();
        std::size_t found = output1.find("scheduled");
        std::size_t found2 = output1.find(std::to_string(package->GetId()));
        bool contains = found != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found2 != std::string::npos;
        EXPECT_TRUE(contains);
        // Check if observer is notified that Robot is moving
        std::size_t found3 = output1.find("moving");
        std::size_t found4 = output1.find(std::to_string(robot->GetId()));
        contains = found3 != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found4 != std::string::npos;
        EXPECT_TRUE(contains);

        std::string X = std::to_string((int) package->GetPosition().at(0));
       std::string Y = std::to_string((int) package->GetPosition().at(1));
       std::string Z = std::to_string((int) package->GetPosition().at(2));
       std::string dronePosition = "[" + X + "," + Y + "," + Z +"]";

       X = std::to_string((int) package->GetPosition().at(0));
       Y = std::to_string((int) package->GetPosition().at(1));
       Z = std::to_string((int) package->GetPosition().at(2));
       std::string packagePosition = "[" + X + "," + Y + "," + Z +"]";


        // Check that the path passed to the notification contains the robot's starting position and package position
        std::size_t found5 = output1.find(packagePosition);
        contains = found5 != std::string::npos;
        EXPECT_TRUE(contains);
        
        std::size_t found6 = output1.find(dronePosition);
        contains = found6 != std::string::npos;
        EXPECT_TRUE(contains);

        // move Robot to package (using default smart path)
        testing::internal::CaptureStdout();
        while(Vector3D(robot->GetPosition()).GetDistance(Vector3D(package->GetPosition())) > 1.0) {
            system->Update(dt);
        }
        // Check if observer is notified that package is en route
        output1 = testing::internal::GetCapturedStdout();
        found = output1.find("en route");
        found2 = output1.find(std::to_string(package->GetId()));
        contains = found != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found2 != std::string::npos;
        EXPECT_TRUE(contains);
        // Check if observer is notified that Robot is moving again to customer
        found3 = output1.find("moving");
        found4 = output1.find(std::to_string(robot->GetId()));
        contains = found3 != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found4 != std::string::npos;
        EXPECT_TRUE(contains);
        // Check that path contains starting position of robot at the package pick-up spot
        found5 = output1.find(packagePosition);
        contains = found5 != std::string::npos;
        EXPECT_TRUE(contains);

        // Check if path contains the final position of the customer
        X = std::to_string((int) package->GetDestination().GetX());
        Y = std::to_string((int) package->GetDestination().GetY());
        Z = std::to_string((int) package->GetDestination().GetZ());
        std::string customerPosition = "[" + X + "," + Y + "," + Z +"]";
        
        found6 = output1.find(customerPosition);
        contains = found6 != std::string::npos;
        EXPECT_TRUE(contains);

        testing::internal::CaptureStdout();
        // Robot moves package to customer
        while(Vector3D(robot->GetPosition()).GetDistance(Vector3D(package->GetDestination())) > 1.0) {
            system->Update(dt);
        }
        system->Update(dt);
        // Check if observer is notified that package is delivered
        output1 = testing::internal::GetCapturedStdout();
        found = output1.find("delivered");
        found2 = output1.find(std::to_string(package->GetId()));
        contains = found != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found2 != std::string::npos;
        EXPECT_TRUE(contains);
        // Check if observer is notified that Robot is no longer moving
        found3 = output1.find("idle");
        found4 = output1.find(std::to_string(robot->GetId()));
        contains = found3 != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found4 != std::string::npos;
        EXPECT_TRUE(contains);     
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