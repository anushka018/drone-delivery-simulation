#include "gtest/gtest.h"
#include "battery.h"

namespace csci3081 {
    class BatteryTest : public ::testing::Test {
        public:
            void SetUp() {
                defaultCharge = 10000;

            }
            void TearDown() {};

        protected:
            float defaultCharge;
            Battery batt;
    };

    TEST_F(BatteryTest, Constructor) {
        batt = Battery();
        EXPECT_EQ(batt.GetMaxCharge(), 10000);
        EXPECT_EQ(batt.GetBatteryReserve(), 10000);
        EXPECT_EQ(batt.IsDead(), false);

        Battery test1 = Battery(0);
        EXPECT_EQ(test1.GetMaxCharge(), 0);
        EXPECT_EQ(test1.GetBatteryReserve(), 0);
        EXPECT_EQ(test1.IsDead(), true);

        Battery test2 = Battery(-10);
        EXPECT_EQ(test2.GetMaxCharge(), 0);
        EXPECT_EQ(test2.GetBatteryReserve(), 0);
        EXPECT_EQ(test2.IsDead(), true);

        Battery test3 = Battery(500);
        EXPECT_EQ(test3.GetMaxCharge(), 500);
        EXPECT_EQ(test3.GetBatteryReserve(), 500);
        EXPECT_EQ(test3.IsDead(), false);

        Battery test4 = Battery(1000000);
        EXPECT_EQ(test4.GetMaxCharge(), 1000000);
        EXPECT_EQ(test4.GetBatteryReserve(), 1000000);
        EXPECT_EQ(test4.IsDead(), false);

        Battery test5 = Battery(1500.045);
        EXPECT_FLOAT_EQ(test5.GetMaxCharge(), 1500.045);
        EXPECT_FLOAT_EQ(test5.GetBatteryReserve(), 1500.045);
        EXPECT_EQ(test5.IsDead(), false);
    }

    TEST_F(BatteryTest, GetMaxCharge) {
        batt = Battery();
        EXPECT_FLOAT_EQ(batt.GetMaxCharge(), 10000);

        Battery test1 = Battery(0);
        EXPECT_FLOAT_EQ(test1.GetMaxCharge(), 0);

        Battery test2 = Battery(-100000);
        EXPECT_FLOAT_EQ(test2.GetMaxCharge(), 0);

        Battery test3 = Battery(-100);
        EXPECT_FLOAT_EQ(test3.GetMaxCharge(), 0);

        Battery test4 = Battery(1000000000);
        EXPECT_FLOAT_EQ(test4.GetMaxCharge(), 1000000000);

        Battery test5 = Battery(999.999);
        EXPECT_FLOAT_EQ(test5.GetMaxCharge(), 999.999);

        Battery test6 = Battery(0.0052);
        EXPECT_FLOAT_EQ(test6.GetMaxCharge(), 0.0052);
        
    }
    TEST_F(BatteryTest, IncreaseCharge) {
        batt = Battery();
        ASSERT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.IncreaseCharge(0);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.IncreaseCharge(0.01);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.IncreaseCharge(10);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.IncreaseCharge(-0.01);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9999.99);

        batt.IncreaseCharge(-1999.99);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 8000);

        batt.IncreaseCharge(1.02);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 8001.02);

        batt.IncreaseCharge(203);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 8204.02);

        batt.IncreaseCharge(2000);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

    }

      TEST_F(BatteryTest, DecreaseCharge) {
        batt = Battery();
        ASSERT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.DecreaseCharge(0);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.DecreaseCharge(0.01);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9999.99);

        batt.DecreaseCharge(10);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9989.99);

        batt.DecreaseCharge(-0.01);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9990);

        batt.DecreaseCharge(400);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9590);

        batt.DecreaseCharge(9000);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 590);

        batt.DecreaseCharge(1000);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 0);

        batt.DecreaseCharge(-1.02);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 1.02);

        batt.DecreaseCharge(-2034.5);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 2035.52);

        batt.DecreaseCharge(-20000);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);
    }


    TEST_F(BatteryTest, GetBatteryReserve) {
        batt = Battery();
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.IncreaseCharge(0);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.IncreaseCharge(20);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 10000);

        batt.DecreaseCharge(0.00001);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9999.9999);

        batt.DecreaseCharge(99.9999);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 9900);

        batt.DecreaseCharge(1000);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 8900);

        batt.DecreaseCharge(1);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 8899);

        batt.DecreaseCharge(0.5);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 8898.5);

        batt.DecreaseCharge(3000.5);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 5898);

        batt.DecreaseCharge(6000);
        EXPECT_FLOAT_EQ(batt.GetBatteryReserve(), 0);

        
    }

    TEST_F(BatteryTest, NoChargeLeft) {
        batt = Battery();
        ASSERT_EQ(batt.IsDead(),false);

        batt.DecreaseCharge(500);
        EXPECT_EQ(batt.IsDead(),false);

        batt.DecreaseCharge(9499.9);
        EXPECT_EQ(batt.IsDead(),false);

        batt.DecreaseCharge(0.01);
        EXPECT_EQ(batt.IsDead(),false);

        batt.DecreaseCharge(0.0001);
        EXPECT_EQ(batt.IsDead(),false);

        batt.DecreaseCharge(0.0899);
        EXPECT_EQ(batt.IsDead(),true);

        batt.DecreaseCharge(2);
        EXPECT_EQ(batt.IsDead(),true);

        batt.IncreaseCharge(5);
        EXPECT_EQ(batt.IsDead(),false);

        batt.DecreaseCharge(100);
        EXPECT_EQ(batt.IsDead(),true);

        batt.IncreaseCharge(10000);
        EXPECT_EQ(batt.IsDead(),false);
    }

}