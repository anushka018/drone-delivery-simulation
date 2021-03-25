#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "package.h"

namespace csci3081 {
    class PackageTest : public ::testing::Test {
        void SetUp() {
            position = {0,0,0};
            direction = {1,0,0};

            packageObj = JsonHelper::CreateJsonObject();
            JsonHelper::AddStringToJsonObject(packageObj, "type", "package");
            JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "position", position);
            JsonHelper::AddStdFloatVectorToJsonObject(packageObj, "direction", direction);

            customerObj = JsonHelper::CreateJsonObject();
            JsonHelper::AddStringToJsonObject(customerObj, "type", "customer");
            JsonHelper::AddStdFloatVectorToJsonObject(customerObj, "position", position);
            JsonHelper::AddStdFloatVectorToJsonObject(customerObj, "direction", direction);
            customer = new Customer(position,direction,customerObj);

        }
        void TearDown() {
            delete customer;
        }

        protected:
            picojson::object packageObj;
            picojson::object customerObj;
            std::vector<float> position;
            std::vector<float> direction;
            Customer* customer;
    };

    TEST_F(PackageTest, DefaultConstructor) {
        // Constructor uses default values for name, weight, speed, radius
        Package package = Package(position,direction, packageObj);
        ASSERT_EQ(picojson::value(package.GetDetails()).serialize(), picojson::value(packageObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(package.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(package.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(package.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(package.GetDirection().at(i), direction.at(i));
        }

        EXPECT_EQ(package.GetId(), package.GetEntityCount());
        EXPECT_EQ(package.GetType(), "package");
        EXPECT_EQ(package.GetVersion(), 0);
        EXPECT_FLOAT_EQ(package.GetRadius(), 1.0);
        EXPECT_EQ((package.GetName()), "Default Package");
        EXPECT_EQ((package.IsDynamic()), false);
        EXPECT_FLOAT_EQ(package.GetWeight(), 10.0);
        EXPECT_FLOAT_EQ(package.GetSpeed(), 0.0);

        EXPECT_EQ(package.GetCustomer(), nullptr);
        EXPECT_EQ(package.GetDestination().GetX(), 0.0);
        EXPECT_EQ(package.GetDestination().GetY(), 0.0);
        EXPECT_EQ(package.GetDestination().GetZ(), 0.0);

    }


    TEST_F(PackageTest, ValuedConstructor) {
        // Testing constructor with no default values
        position = {1000,2000,-5};
        direction = {0,0,1};
        Package package = Package(position,direction, packageObj, "Amazon Delivery", 18.2, 2.5, 3.0);
        ASSERT_EQ(picojson::value(package.GetDetails()).serialize(), picojson::value(packageObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(package.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(package.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(package.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(package.GetDirection().at(i), direction.at(i));
        }

        EXPECT_EQ(package.GetId(), package.GetEntityCount());
        EXPECT_EQ(package.GetType(), "package");
        EXPECT_EQ(package.GetVersion(), 0);
        EXPECT_FLOAT_EQ(package.GetRadius(), 3.0);
        EXPECT_EQ((package.GetName()), "Amazon Delivery");
        EXPECT_FALSE(package.IsDynamic());
        EXPECT_FLOAT_EQ(package.GetWeight(), 18.2);
        EXPECT_FLOAT_EQ(package.GetSpeed(), 2.5);

        EXPECT_EQ(package.GetCustomer(), nullptr);
        EXPECT_EQ(package.GetDestination().GetX(), 0.0);
        EXPECT_EQ(package.GetDestination().GetY(), 0.0);
        EXPECT_EQ(package.GetDestination().GetZ(), 0.0);

        // Testing constructor with default value for radius
        position = {10000000,3200,0.2};
        direction = {3,1,1};
        package = Package(position,direction, packageObj, "feather", 0.001, 0.5);
        ASSERT_EQ(picojson::value(package.GetDetails()).serialize(), picojson::value(packageObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(package.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(package.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(package.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(package.GetDirection().at(i), direction.at(i));
        }

        EXPECT_EQ(package.GetId(), package.GetEntityCount());
        EXPECT_EQ(package.GetType(), "package");
        EXPECT_EQ(package.GetVersion(), 0);
        EXPECT_FLOAT_EQ(package.GetRadius(), 1.0);
        EXPECT_EQ((package.GetName()), "feather");
        EXPECT_FALSE(package.IsDynamic());
        EXPECT_FLOAT_EQ(package.GetWeight(), 0.001);
        EXPECT_FLOAT_EQ(package.GetSpeed(), 0.5);

        EXPECT_EQ(package.GetCustomer(), nullptr);
        EXPECT_EQ(package.GetDestination().GetX(), 0.0);
        EXPECT_EQ(package.GetDestination().GetY(), 0.0);
        EXPECT_EQ(package.GetDestination().GetZ(), 0.0);

        // Testing constructor with default value for speed and radius
        package = Package(position,direction, packageObj, "Heavy Package", 1234);
        ASSERT_EQ(picojson::value(package.GetDetails()).serialize(), picojson::value(packageObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(package.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(package.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(package.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(package.GetDirection().at(i), direction.at(i));
        }

        EXPECT_EQ(package.GetId(), package.GetEntityCount());
        EXPECT_EQ(package.GetType(), "package");
        EXPECT_EQ(package.GetVersion(), 0);
        EXPECT_FLOAT_EQ(package.GetRadius(), 1.0);
        EXPECT_EQ((package.GetName()), "Heavy Package");
        EXPECT_FALSE(package.IsDynamic());
        EXPECT_FLOAT_EQ(package.GetWeight(), 1234);
        EXPECT_FLOAT_EQ(package.GetSpeed(), 0.0);

        EXPECT_EQ(package.GetCustomer(), nullptr);
        EXPECT_EQ(package.GetDestination().GetX(), 0.0);
        EXPECT_EQ(package.GetDestination().GetY(), 0.0);
        EXPECT_EQ(package.GetDestination().GetZ(), 0.0);

        // Testing constructor with default value for speed, radius, and weight
        package = Package(position,direction, packageObj, "just your average cardboard box");
        ASSERT_EQ(picojson::value(package.GetDetails()).serialize(), picojson::value(packageObj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(package.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(package.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(package.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(package.GetDirection().at(i), direction.at(i));
        }

        EXPECT_EQ(package.GetId(), package.GetEntityCount());
        EXPECT_EQ(package.GetType(), "package");
        EXPECT_EQ(package.GetVersion(), 0);
        EXPECT_FLOAT_EQ(package.GetRadius(), 1.0);
        EXPECT_EQ((package.GetName()), "just your average cardboard box");
        EXPECT_FALSE(package.IsDynamic());
        EXPECT_FLOAT_EQ(package.GetWeight(), 10.0);
        EXPECT_FLOAT_EQ(package.GetSpeed(), 0.0);

        EXPECT_EQ(package.GetCustomer(), nullptr);
        EXPECT_EQ(package.GetDestination().GetX(), 0.0);
        EXPECT_EQ(package.GetDestination().GetY(), 0.0);
        EXPECT_EQ(package.GetDestination().GetZ(), 0.0);
    }


    TEST_F(PackageTest, GetSetCustomer) {
        Package package = Package(position,direction, packageObj);
        EXPECT_TRUE(package.GetCustomer() == nullptr);

        package.SetCustomer(customer);
        EXPECT_TRUE(package.GetCustomer() != nullptr);
        EXPECT_EQ(picojson::value(package.GetCustomer()->GetDetails()).serialize(), picojson::value(customerObj).serialize());
        EXPECT_EQ(package.GetCustomer()->GetType(), "customer");
        EXPECT_EQ(package.GetCustomer()->GetVersion(), 0);
        EXPECT_FLOAT_EQ(package.GetCustomer()->GetRadius(), 1.0);
        EXPECT_EQ((package.GetCustomer()->GetName()), "Default Customer");
        EXPECT_FLOAT_EQ((package.GetCustomer()->IsDynamic()), false);

    }

    TEST_F(PackageTest, GetSetDestination) {
        Package package = Package(position,direction, packageObj);
        EXPECT_FLOAT_EQ(package.GetDestination().GetX(), 0.0);
        EXPECT_FLOAT_EQ(package.GetDestination().GetY(), 0.0);
        EXPECT_FLOAT_EQ(package.GetDestination().GetZ(), 0.0);
        
        Vector3D dest = Vector3D(5.0,10.0,-2.5);
        package.SetDestination(dest);
        EXPECT_FLOAT_EQ(package.GetDestination().GetX(), 5.0);
        EXPECT_FLOAT_EQ(package.GetDestination().GetY(), 10.0);
        EXPECT_FLOAT_EQ(package.GetDestination().GetZ(), -2.5);

        dest = Vector3D(0.01,-0.004,0.0000039);
        package.SetDestination(dest);
        EXPECT_FLOAT_EQ(package.GetDestination().GetX(), 0.01);
        EXPECT_FLOAT_EQ(package.GetDestination().GetY(), -0.004);
        EXPECT_FLOAT_EQ(package.GetDestination().GetZ(), 0.0000039);

        dest = Vector3D(-4356000,6043,9000000000);
        package.SetDestination(dest);
        EXPECT_FLOAT_EQ(package.GetDestination().GetX(), -4356000);
        EXPECT_FLOAT_EQ(package.GetDestination().GetY(), 6043);
        EXPECT_FLOAT_EQ(package.GetDestination().GetZ(), 9000000000);
    }
}