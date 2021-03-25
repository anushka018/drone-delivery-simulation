#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "customer.h"


namespace csci3081 {
    using entity_project::IEntity;

    class CustomerTest: public ::testing::Test {
        public: 
            void SetUp() {
                
                system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));

                position = {20.3,10.2,5.0};
                direction = {1,0,1};
                obj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(obj, "type", "customer");
                JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position);
                JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction);
            }
            void TearDown() {};

        protected:
            IDeliverySystem* system;
            picojson::object obj;
            std::vector<float> position;
            std::vector<float> direction;

    };

    TEST_F(CustomerTest, DefaultConstructor) {
        // Constructor uses default values for name, speed, and radius
        Customer cust = Customer(position, direction, obj);
        ASSERT_EQ(picojson::value(cust.GetDetails()).serialize(), picojson::value(obj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(cust.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(cust.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(cust.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(cust.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(cust.GetId(), cust.GetEntityCount());
        EXPECT_EQ(cust.GetVersion(), 0);
        EXPECT_FLOAT_EQ(cust.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(cust.GetSpeed(), 0.0);
        EXPECT_EQ((cust.GetName()), "Default Customer");
        EXPECT_EQ((cust.GetType()), "customer");
        EXPECT_FALSE(cust.IsDynamic());
    }

    TEST_F(CustomerTest, ValuedConstructor) {
        // Testing Constructor with no default values
        position = {-5.0,10.2,-3.4};
        direction = {0,0,0};

        Customer cust = Customer(position, direction, obj, "Mr. Robot", 5.0, 1.5);
        ASSERT_EQ(picojson::value(cust.GetDetails()).serialize(), picojson::value(obj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(cust.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(cust.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(cust.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(cust.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(cust.GetId(), cust.GetEntityCount());
        EXPECT_EQ(cust.GetVersion(), 0);
        EXPECT_FLOAT_EQ(cust.GetRadius(), 1.5);
        EXPECT_FLOAT_EQ(cust.GetSpeed(), 5.0);
        EXPECT_EQ((cust.GetName()), "Mr. Robot");
        EXPECT_EQ((cust.GetType()), "customer");
        EXPECT_FALSE(cust.IsDynamic());

        // Testing constructor using default value for speed and radius
        position = {-5000,-24800,305};
        direction = {0.33,0.33,0.33};

        cust = Customer(position, direction, obj, "Angry Customer");
        ASSERT_EQ(picojson::value(cust.GetDetails()).serialize(), picojson::value(obj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(cust.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(cust.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(cust.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(cust.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(cust.GetId(), cust.GetEntityCount());
        EXPECT_EQ(cust.GetVersion(), 0);
        EXPECT_FLOAT_EQ(cust.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(cust.GetSpeed(), 0.0);
        EXPECT_EQ((cust.GetName()), "Angry Customer");
        EXPECT_EQ((cust.GetType()), "customer");
        EXPECT_FALSE(cust.IsDynamic());

        // Testing constructor using default value for just radius
        position = {0.056,-0.008,1.02};
        direction = {0.50,0.50,2};

        cust = Customer(position, direction, obj, "Anxiously Speeding", 1000);
        ASSERT_EQ(picojson::value(cust.GetDetails()).serialize(), picojson::value(obj).serialize());
        // Testing Position Attribute
        // std::vector<float> posVector
        ASSERT_EQ(cust.GetPosition().size(), position.size());
        for (int i = 0; i < position.size(); i++) {
            EXPECT_EQ(cust.GetPosition().at(i), position.at(i));
        }
        // Testing Direction Attribute
        // std::vector<float> dirVector
        ASSERT_EQ(cust.GetDirection().size(), direction.size());
        for (int i = 0; i < direction.size(); i++) {
            EXPECT_EQ(cust.GetDirection().at(i), direction.at(i));
        }
        // Testing Attributes initialized by Entity Base Constructor
        EXPECT_EQ(cust.GetId(), cust.GetEntityCount());
        EXPECT_EQ(cust.GetVersion(), 0);
        EXPECT_FLOAT_EQ(cust.GetRadius(), 1.0);
        EXPECT_FLOAT_EQ(cust.GetSpeed(), 1000);
        EXPECT_EQ((cust.GetName()), "Anxiously Speeding");
        EXPECT_EQ((cust.GetType()), "customer");
        EXPECT_FALSE(cust.IsDynamic());
    }

}