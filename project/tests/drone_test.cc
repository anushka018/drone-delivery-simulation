#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/osm_graph_parser.h>
#include <EntityProject/entity_console_logger.h>
#include <EntityProject/graph.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"

namespace csci3081 {
    class DroneTest : public ::testing::Test {
        public:
            void SetUp() {
                system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));

                position = {0,0,0};
                direction = {1,0,0};
                droneObj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(droneObj, "type", "drone");
                JsonHelper::AddFloatToJsonObject(droneObj, "radius", 1.0);
                JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(droneObj, "direction", direction);

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

                path = {{2,0,0},{0,2,0},{5,4,3},{0,0,0}, {20,264,-15}, {100,264,17}};
            }
            void TearDown() {};

        protected:
            IDeliverySystem* system;
            picojson::object droneObj;
            picojson::object packageObj;
            picojson::object customerObj;
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

        // Speed is 10.0 and dt is 0.10
        // Robot has reached (1.1,0,0) and is now headed to (2,0,0)
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 2.1, 0.001);
        EXPECT_NEAR(newPos.at(1), 0, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);

        // Robot has reached (2,0,0) and is now headed to (0,2,0)
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 1.376, 0.001);
        EXPECT_NEAR(newPos.at(1), 0.689, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), -0.724, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0.690, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0, 0.001);

        drone.Update(dt);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), -0.072, 0.001);
        EXPECT_NEAR(newPos.at(1), 2.069, 0.001);
        EXPECT_NEAR(newPos.at(2), 0, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), -0.724, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0.690, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0, 0.001);
  
        // Robot has reached point 2, moving to (5,4,3)
        drone.Update(dt);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 1.563, 0.001);
        EXPECT_NEAR(newPos.at(1), 2.692, 0.001);
        EXPECT_NEAR(newPos.at(2), 0.968, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(0), 0.817, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0.311, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0.484, 0.001);

        drone.Update(dt);
        drone.Update(dt);
        drone.Update(dt);
        drone.Update(dt);
        newPos = drone.GetPosition();
        ASSERT_EQ(newPos.size(), drone.GetPosition().size());
        for (int i = 0; i < newPos.size(); i++) {
            EXPECT_FLOAT_EQ(drone.GetPosition().at(i), newPos.at(i));
        }
        EXPECT_NEAR(newPos.at(0), 5.0, 0.5);
        EXPECT_NEAR(newPos.at(1), 4.0, 0.5);
        EXPECT_NEAR(newPos.at(2), 3.0, 0.5);
        EXPECT_NEAR(drone.GetDirection().at(0), 0.817, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(1), 0.311, 0.001);
        EXPECT_NEAR(drone.GetDirection().at(2), 0.484, 0.001);

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
        delete package;
    }

    // Update Test Part 3: Check for the proper observer notifications during the simulation
    TEST_F(DroneTest, UpdateObservers) {
        // Create and set the graph
        if (system) {
            entity_project::OSMGraphParser parser;
            const IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
            system->SetGraph(graph);
        }

        entity_project::EntityConsoleLogger logger;
        system->AddObserver(&logger);
        
        IEntity* droneEntity = system->CreateEntity(droneObj);
        IEntity* packageEntity = system->CreateEntity(packageObj);
        IEntity* customerEntity = system->CreateEntity(customerObj);

        system->AddEntity(droneEntity);
        system->AddEntity(packageEntity);
        system->AddEntity(customerEntity);
        BatteryDroneDecorator* drone = dynamic_cast<BatteryDroneDecorator*>(droneEntity);
        drone->SetSpeed(30.0);
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
        // Check if observer is notified that drone is moving
        std::size_t found3 = output1.find("moving");
        std::size_t found4 = output1.find(std::to_string(drone->GetId()));
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

        // Check that the path passed to the notification contains the drone's starting position and package position
        std::size_t found5 = output1.find(packagePosition);
        contains = found5 != std::string::npos;
        EXPECT_TRUE(contains);
        
        std::size_t found6 = output1.find(dronePosition);
        contains = found6 != std::string::npos;
        EXPECT_TRUE(contains);
    
        // move drone to package (using default smart path)
        testing::internal::CaptureStdout();
        while(Vector3D(drone->GetPosition()).GetDistance(Vector3D(package->GetPosition())) > 1.0) {
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
        // Check if observer is notified that drone is moving again to customer
        found3 = output1.find("moving");
        found4 = output1.find(std::to_string(drone->GetId()));
        contains = found3 != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found4 != std::string::npos;
        EXPECT_TRUE(contains);

        // Check that path contains starting position of drone at the package pick-up spot
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
        
        // drone moves package to customer
        while(Vector3D(drone->GetPosition()).GetDistance(Vector3D(package->GetDestination())) > 1.0) {
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
        // Check if observer is notified that drone is no longer moving
        found3 = output1.find("idle");
        found4 = output1.find(std::to_string(drone->GetId()));
        contains = found3 != std::string::npos;
        EXPECT_TRUE(contains);
        contains = found4 != std::string::npos;
        EXPECT_TRUE(contains);     
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




