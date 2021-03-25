#include "vector2D.h"
#include <iostream> 
#include "gtest/gtest.h"

namespace csci3081 {
    class Vector2D_Test : public ::testing::Test {
        public:
            void SetUp() {
                zero = Vector2D();
                xAxis = Vector2D(1.0, 0.0);
                zAxis = Vector2D(0.0, 1.0);
                posOne = Vector2D(1.0, 1.0);
                negOne = Vector2D(-1.0, -1.0);
                vec = Vector2D(206.543, -4098.0001);
            }
            void TearDown() {}
        protected:
            Vector2D zero;
            Vector2D xAxis;
            Vector2D zAxis;
            Vector2D posOne;
            Vector2D negOne;
            Vector2D vec;
    };

    TEST_F(Vector2D_Test, DefaultConstructor) {
        EXPECT_FLOAT_EQ(zero.GetX(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetY(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetZ(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetMagnitude(), 0.0);
    }

    TEST_F(Vector2D_Test, Constructor) {
        Vector2D defaultZ = Vector2D(5.0, 4.0);
        EXPECT_FLOAT_EQ(defaultZ.GetX(), 5.0);
        EXPECT_FLOAT_EQ(defaultZ.GetY(), 0.0);
        EXPECT_FLOAT_EQ(defaultZ.GetZ(), 4.0);

        Vector2D defaultYZ = Vector2D(10.0, 0.0);
        EXPECT_FLOAT_EQ(defaultYZ.GetX(), 10.0);
        EXPECT_FLOAT_EQ(defaultYZ.GetY(), 0.0);
        EXPECT_FLOAT_EQ(defaultYZ.GetZ(), 0.0);
        
        Vector2D pos = Vector2D(5.004, 90.01);
        EXPECT_FLOAT_EQ(pos.GetX(), 5.004);
        EXPECT_FLOAT_EQ(pos.GetZ(), 90.01);
        
        Vector2D bigPos = Vector2D(20487.209, 43654.954);
        EXPECT_FLOAT_EQ(bigPos.GetX(), 20487.209);
        EXPECT_FLOAT_EQ(bigPos.GetY(), 0.0);
        EXPECT_FLOAT_EQ(bigPos.GetZ(), 43654.954);

        Vector2D neg = Vector2D(-0.00001, -4.409);
        EXPECT_FLOAT_EQ(neg.GetX(), -0.00001);
        EXPECT_FLOAT_EQ(neg.GetY(), 0.0);
        EXPECT_FLOAT_EQ(neg.GetZ(), -4.409);

        Vector2D bigNeg = Vector2D(-32709.84, -984.4);
        EXPECT_FLOAT_EQ(bigNeg.GetX(), -32709.84);
        EXPECT_FLOAT_EQ(bigNeg.GetY(), 0.0);
        EXPECT_FLOAT_EQ(bigNeg.GetZ(), -984.4);
        
        Vector2D mix = Vector2D(-12.34, 412.0);
        EXPECT_FLOAT_EQ(mix.GetX(), -12.34);
        EXPECT_FLOAT_EQ(mix.GetY(), 0.0);
        EXPECT_FLOAT_EQ(mix.GetZ(), 412.0);

        
        Vector2D upper = Vector2D(3.4e+38, 3.4e+38);
        EXPECT_FLOAT_EQ(upper.GetX(), 3.4e+38);
        EXPECT_FLOAT_EQ(upper.GetY(), 0.0);
        EXPECT_FLOAT_EQ(upper.GetZ(), 3.4e+38);

        Vector2D posMiddle = Vector2D(1.7e+19, 1.7e+19);
        EXPECT_FLOAT_EQ(posMiddle.GetX(), 1.7e+19);
        EXPECT_FLOAT_EQ(posMiddle.GetY(), 0.0);
        EXPECT_FLOAT_EQ(posMiddle.GetZ(), 1.7e+19);

        Vector2D negMiddle = Vector2D(-1.7e+19, -1.7e+19);
        EXPECT_FLOAT_EQ(negMiddle.GetX(), -1.7e+19);
        EXPECT_FLOAT_EQ(negMiddle.GetY(), 0.0);
        EXPECT_FLOAT_EQ(negMiddle.GetZ(), -1.7e+19);

        Vector2D lower = Vector2D(-3.4e+38, -3.4e+38);
        EXPECT_FLOAT_EQ(lower.GetX(), -3.4e+38);
        EXPECT_FLOAT_EQ(lower.GetY(), 0.0);
        EXPECT_FLOAT_EQ(lower.GetZ(), -3.4e+38);
    }


    TEST_F(Vector2D_Test, AssignmentOperator) {
        Vector2D zeroCopy;
        zeroCopy = zero;
        EXPECT_FLOAT_EQ(zeroCopy.GetX(), 0.0);
        EXPECT_FLOAT_EQ(zeroCopy.GetY(), 0.0);
        EXPECT_FLOAT_EQ(zeroCopy.GetZ(), 0.0);

        Vector2D posOneCopy;
        posOneCopy = posOne;
        EXPECT_FLOAT_EQ(posOneCopy.GetX(), 1.0);
        EXPECT_FLOAT_EQ(posOneCopy.GetY(), 0.0);
        EXPECT_FLOAT_EQ(posOneCopy.GetZ(), 1.0);

        Vector3D vecCopy = vec;
        EXPECT_FLOAT_EQ(vecCopy.GetX(), 206.543);
        EXPECT_FLOAT_EQ(vecCopy.GetY(), 0);
        EXPECT_FLOAT_EQ(vecCopy.GetZ(), -4098.0001);

    }

    TEST_F(Vector2D_Test, Addition) {
        Vector2D add1 = (zero + posOne);
        EXPECT_FLOAT_EQ(add1.GetX(), 1.0);
        EXPECT_FLOAT_EQ(add1.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add1.GetZ(), 1.0);

        Vector2D add2 = (zero + xAxis);
        EXPECT_FLOAT_EQ(add2.GetX(), 1.0);
        EXPECT_FLOAT_EQ(add2.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add2.GetZ(), 0.0);

        Vector2D add3 = (posOne + xAxis);
        EXPECT_FLOAT_EQ(add3.GetX(), 2.0);
        EXPECT_FLOAT_EQ(add3.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add3.GetZ(), 1.0);

        Vector2D add4 = zero + zAxis;
        EXPECT_FLOAT_EQ(add4.GetX(), 0.0);
        EXPECT_FLOAT_EQ(add4.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add4.GetZ(), 1.0);

        Vector2D add5 = vec + zero;
        EXPECT_FLOAT_EQ(add5.GetX(), 206.543);
        EXPECT_FLOAT_EQ(add5.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add5.GetZ(), -4098.0001);

        Vector2D add6 = vec + posOne;
        EXPECT_FLOAT_EQ(add6.GetX(), 207.543);
        EXPECT_FLOAT_EQ(add6.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add6.GetZ(), -4097.0001);

        Vector2D add7 = vec + negOne;
        EXPECT_FLOAT_EQ(add7.GetX(), 205.543);
        EXPECT_FLOAT_EQ(add7.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add7.GetZ(), -4099.0001);
                               

    }
    TEST_F(Vector2D_Test, Increment) {
        Vector2D v  = Vector2D(); // default values of 0.0 for x,y,z
        v += zero;
        EXPECT_FLOAT_EQ(v.GetX(), 0.0);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 0.0);

        v += posOne;
        EXPECT_FLOAT_EQ(v.GetX(), 1.0);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 1.0);

        v += vec;
        EXPECT_FLOAT_EQ(v.GetX(), 207.543);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), -4097.0001);

        v += negOne;
        EXPECT_FLOAT_EQ(v.GetX(), 206.543);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), -4098.0001);

        Vector2D thousand = Vector2D(1000.0, 1000.0);
        v += thousand;
        EXPECT_FLOAT_EQ(v.GetX(), 1206.543);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), -3098.0001);

    }

    TEST_F(Vector2D_Test, Subtraction) {
        Vector2D sub1 = zero - posOne;
        EXPECT_FLOAT_EQ(sub1.GetX(), -1.0);
        EXPECT_FLOAT_EQ(sub1.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub1.GetZ(), -1.0);

        Vector2D sub2 = zero - xAxis;
        EXPECT_FLOAT_EQ(sub2.GetX(), -1.0);
        EXPECT_FLOAT_EQ(sub2.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub2.GetZ(), 0.0);

        Vector2D sub3 = posOne - xAxis;
        EXPECT_FLOAT_EQ(sub3.GetX(), 0.0);
        EXPECT_FLOAT_EQ(sub3.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub3.GetZ(), 1.0);

        Vector2D sub4 = zero - zAxis;
        EXPECT_FLOAT_EQ(sub4.GetX(), 0.0);
        EXPECT_FLOAT_EQ(sub4.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub4.GetZ(), -1.0);

        Vector2D sub5 = vec - zero;
        EXPECT_FLOAT_EQ(sub5.GetX(), 206.543);
        EXPECT_FLOAT_EQ(sub5.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub5.GetZ(), -4098.0001);

        Vector2D sub6 = vec - posOne;
        EXPECT_FLOAT_EQ(sub6.GetX(), 205.543);
        EXPECT_FLOAT_EQ(sub6.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub6.GetZ(), -4099.0001);

        Vector2D sub7 = vec - negOne;
        EXPECT_FLOAT_EQ(sub7.GetX(), 207.543);
        EXPECT_FLOAT_EQ(sub7.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub7.GetZ(), -4097.0001);

    }
    TEST_F(Vector2D_Test, Decrement) {
        Vector2D v  = Vector2D(); // default values of 0.0 for x,y,z
        v -= posOne;
        EXPECT_FLOAT_EQ(v.GetX(), -1.0);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), -1.0);

        v -= vec;
        EXPECT_FLOAT_EQ(v.GetX(), -207.543);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 4097.0001);

        v -= negOne;
        EXPECT_FLOAT_EQ(v.GetX(), -206.543);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 4098.0001);

        Vector2D thousand = Vector2D(1000.0,1000.0);
        v -= thousand;
        EXPECT_FLOAT_EQ(v.GetX(), -1206.543);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 3098.0001);

    }
    TEST_F(Vector2D_Test, Multiplication) {
        Vector2D multTest = zero * 0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = zero * 8;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = posOne * 1;
        EXPECT_FLOAT_EQ(multTest.GetX(), 1.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 1.0);

        multTest = posOne * 5;
        EXPECT_FLOAT_EQ(multTest.GetX(), 5.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 5.0);

        multTest = posOne * -100;
        EXPECT_FLOAT_EQ(multTest.GetX(), -100.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -100.0);

        multTest = xAxis * 1;
        EXPECT_FLOAT_EQ(multTest.GetX(), 1.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = negOne * 1;
        EXPECT_FLOAT_EQ(multTest.GetX(), -1.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -1.0);

        multTest = negOne * 0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);
        
        multTest = negOne * -0.25;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.25);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.25);

        multTest = negOne * 14.5;
        EXPECT_FLOAT_EQ(multTest.GetX(), -14.5);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -14.5);

    }

    TEST_F(Vector2D_Test, MultiplicationAssignment) {
        Vector2D multTest = Vector2D();
        multTest *= 0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest *= 10.0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = Vector2D(1.0,1.0);
        multTest *= 100.0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 100.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 100.0);

        multTest *= 0.5;
        EXPECT_FLOAT_EQ(multTest.GetX(), 50.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 50.0);

        multTest *= -0.1;
        EXPECT_FLOAT_EQ(multTest.GetX(), -5.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -5.0);

        multTest *= -2;
        EXPECT_FLOAT_EQ(multTest.GetX(), 10.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 10.0);
        

    }

    TEST_F(Vector2D_Test, GetMagnitude) {
        EXPECT_FLOAT_EQ(zero.GetMagnitude(), 0.0);
        EXPECT_FLOAT_EQ(xAxis.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(zAxis.GetMagnitude(), 1.0);

        EXPECT_FLOAT_EQ(posOne.GetMagnitude(), 1.41421356);
        EXPECT_FLOAT_EQ(negOne.GetMagnitude(), 1.41421356);
        EXPECT_FLOAT_EQ(vec.GetMagnitude(), 4103.201778);
    }

    TEST_F(Vector2D_Test, Normalize) {
        zero.Normalize();
        EXPECT_FLOAT_EQ(zero.GetX(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetY(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetZ(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetMagnitude(), 0.0);


        Vector2D v = Vector2D(3.0, 4.0);
        v.Normalize();
        EXPECT_FLOAT_EQ(v.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(v.GetX(), 0.6);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 0.8);

        Vector2D one = Vector2D(0.0, 1.0);
        one.Normalize();
        EXPECT_FLOAT_EQ(one.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(one.GetX(), 0.0);
        EXPECT_FLOAT_EQ(one.GetY(), 0.0);
        EXPECT_FLOAT_EQ(one.GetZ(), 1.0);

    }

    TEST_F(Vector2D_Test, IsNormalized) {
        EXPECT_EQ(xAxis.IsNormalized(), true);
        EXPECT_EQ(zAxis.IsNormalized(), true);
        EXPECT_EQ(zero.IsNormalized(), false);
        EXPECT_EQ(posOne.IsNormalized(), false);
        EXPECT_EQ(vec.IsNormalized(), false);

        Vector2D v = Vector2D(3.0, 4.0);
        v.Normalize();
        EXPECT_EQ(v.IsNormalized(), true);

        v = Vector2D(3000000, -4e9);
        v.Normalize();
        EXPECT_EQ(v.IsNormalized(), true);

        v = Vector2D(3, -4e-9);
        v.Normalize();
        EXPECT_EQ(v.IsNormalized(), true);
        
    }

    TEST_F(Vector2D_Test, GetDistance) {
        EXPECT_FLOAT_EQ(posOne.GetDistance(zero), 1.41421356);
        EXPECT_FLOAT_EQ(negOne.GetDistance(zero), 1.41421356);

        EXPECT_FLOAT_EQ(xAxis.GetDistance(zero), 1.0);
        EXPECT_FLOAT_EQ(zAxis.GetDistance(zero), 1.0);

        EXPECT_FLOAT_EQ(vec.GetDistance(zero), vec.GetMagnitude());

        Vector2D copyOne = Vector2D();
        copyOne = posOne;
        EXPECT_FLOAT_EQ(copyOne.GetDistance(posOne), 0.0);
        
    }
    
    TEST_F(Vector2D_Test, GetVector) {
        std::vector<float> v = zero.GetVector();

        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), zero.GetX());
        EXPECT_EQ(v.at(1), zero.GetY());
        EXPECT_EQ(v.at(2), zero.GetZ());
    
        v = xAxis.GetVector();
        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), xAxis.GetX());
        EXPECT_EQ(v.at(1), xAxis.GetY());
        EXPECT_EQ(v.at(2), xAxis.GetZ());

        v = zAxis.GetVector();
        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), zAxis.GetX());
        EXPECT_EQ(v.at(1), zAxis.GetY());
        EXPECT_EQ(v.at(2), zAxis.GetZ());

        v = posOne.GetVector();
        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), posOne.GetX());
        EXPECT_EQ(v.at(1), posOne.GetY());
        EXPECT_EQ(v.at(2), posOne.GetZ());

        v = negOne.GetVector();
        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), negOne.GetX());
        EXPECT_EQ(v.at(1), negOne.GetY());
        EXPECT_EQ(v.at(2), negOne.GetZ());

        v = vec.GetVector();
        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), vec.GetX());
        EXPECT_EQ(v.at(1), vec.GetY());
        EXPECT_EQ(v.at(2), vec.GetZ());
    }
    

    TEST_F(Vector2D_Test, Display) {
        std::string expected_out_1 = "(0.000, 0.000)\n";
        std::string expected_out_2 = "(1.000, 0.000)\n";
        std::string expected_out_3 = "(0.000, 1.000)\n";
        std::string expected_out_4 = "(1.000, 1.000)\n";
        std::string expected_out_5 = "(-1.000, -1.000)\n";
        std::string expected_out_6 = "(206.543, -4098.000)\n";
  
        testing::internal::CaptureStdout();
        zero.Display();
        std::string output1 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout(); 
        xAxis.Display();
        std::string output2 = testing::internal::GetCapturedStdout();

        testing::internal::CaptureStdout();
        zAxis.Display();
        std::string output3 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout(); 
        posOne.Display();
        std::string output4 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout();
        negOne.Display();
        std::string output5 = testing::internal::GetCapturedStdout();

        testing::internal::CaptureStdout();
        vec.Display();
        std::string output6 = testing::internal::GetCapturedStdout();
  
        EXPECT_EQ(output1, expected_out_1);
        EXPECT_EQ(output2, expected_out_2);
        EXPECT_EQ(output3, expected_out_3);
        EXPECT_EQ(output4, expected_out_4);
        EXPECT_EQ(output5, expected_out_5);
        EXPECT_EQ(output6, expected_out_6);
        

    };

}