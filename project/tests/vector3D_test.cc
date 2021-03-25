#include "vector3D.h"
#include <iostream> 
#include "gtest/gtest.h"

namespace csci3081 {
    class Vector3D_Test : public ::testing::Test {
        public:
            void SetUp() {
                zero = Vector3D();
                xAxis = Vector3D(1.0, 0.0, 0.0);
                yAxis = Vector3D(0.0, 1.0, 0.0);
                zAxis = Vector3D(0.0, 0.0, 1.0);
                posOne = Vector3D(1.0, 1.0, 1.0);
                negOne = Vector3D(-1.0, -1.0, -1.0);
                vec = Vector3D(1.5, 30.65, -5.67);
            }
            void TearDown() {}
        protected:
            Vector3D zero;
            Vector3D xAxis;
            Vector3D yAxis;
            Vector3D zAxis;
            Vector3D posOne;
            Vector3D negOne;
            Vector3D vec;
    };

    TEST_F(Vector3D_Test, DefaultConstructor) {
        EXPECT_FLOAT_EQ(zero.GetX(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetY(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetZ(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetMagnitude(), 0.0);
    }

    TEST_F(Vector3D_Test, VectorConstructor) {
        std::vector<float> test = {0,0,0};
        Vector3D fromVec1 = Vector3D(test);
        EXPECT_FLOAT_EQ(fromVec1.GetX(), 0.0);
        EXPECT_FLOAT_EQ(fromVec1.GetY(), 0.0);
        EXPECT_FLOAT_EQ(fromVec1.GetZ(), 0.0);

        test = {1.0,1.0,1.0};
        Vector3D fromVec2 = Vector3D(test);
        EXPECT_FLOAT_EQ(fromVec2.GetX(), 1.0);
        EXPECT_FLOAT_EQ(fromVec2.GetY(), 1.0);
        EXPECT_FLOAT_EQ(fromVec2.GetZ(), 1.0);

        test = {-1.0,-1.0,-1.0};
        Vector3D fromVec3 = Vector3D(test);
        EXPECT_FLOAT_EQ(fromVec3.GetX(), -1.0);
        EXPECT_FLOAT_EQ(fromVec3.GetY(), -1.0);
        EXPECT_FLOAT_EQ(fromVec3.GetZ(), -1.0);

        test = {0.0,9.4};
        Vector3D fromVec4 = Vector3D(test);
        EXPECT_FLOAT_EQ(fromVec4.GetX(), 0.0);
        EXPECT_FLOAT_EQ(fromVec4.GetY(), 0.0);
        EXPECT_FLOAT_EQ(fromVec4.GetZ(), 0.0);

        test = {15.2};
        Vector3D fromVec5 = Vector3D(test);
        EXPECT_FLOAT_EQ(fromVec5.GetX(), 0.0);
        EXPECT_FLOAT_EQ(fromVec5.GetY(), 0.0);
        EXPECT_FLOAT_EQ(fromVec5.GetZ(), 0.0);

        test = {15.2, 10.2, 3.4, 4.5};
        Vector3D fromVec6 = Vector3D(test);
        EXPECT_FLOAT_EQ(fromVec6.GetX(), .0);
        EXPECT_FLOAT_EQ(fromVec6.GetY(), 0.0);
        EXPECT_FLOAT_EQ(fromVec6.GetZ(), 0.0);



    }

    TEST_F(Vector3D_Test, ValuesConstructor) {
        Vector3D defaultZ = Vector3D(5.0, 4.0);
        EXPECT_FLOAT_EQ(defaultZ.GetX(), 5.0);
        EXPECT_FLOAT_EQ(defaultZ.GetY(), 4.0);
        EXPECT_FLOAT_EQ(defaultZ.GetZ(), 0.0);

        Vector3D defaultYZ = Vector3D(10.0);
        EXPECT_FLOAT_EQ(defaultYZ.GetX(), 10.0);
        EXPECT_FLOAT_EQ(defaultYZ.GetY(), 0.0);
        EXPECT_FLOAT_EQ(defaultYZ.GetZ(), 0.0);
        
        Vector3D pos = Vector3D(2.2, 3.1, 4.9);
        EXPECT_FLOAT_EQ(pos.GetX(), 2.2);
        EXPECT_FLOAT_EQ(pos.GetY(), 3.1);
        EXPECT_FLOAT_EQ(pos.GetZ(), 4.9);
        
        Vector3D bigPos = Vector3D(20487.209, 3000000.123, 43654.954);
        EXPECT_FLOAT_EQ(bigPos.GetX(), 20487.209);
        EXPECT_FLOAT_EQ(bigPos.GetY(), 3000000.123);
        EXPECT_FLOAT_EQ(bigPos.GetZ(), 43654.954);

        Vector3D neg = Vector3D(-3.8, -3.2, -4.4);
        EXPECT_FLOAT_EQ(neg.GetX(), -3.8);
        EXPECT_FLOAT_EQ(neg.GetY(), -3.2);
        EXPECT_FLOAT_EQ(neg.GetZ(), -4.4);

        Vector3D bigNeg = Vector3D(-32709.84, -10287.21, -984.4);
        EXPECT_FLOAT_EQ(bigNeg.GetX(), -32709.84);
        EXPECT_FLOAT_EQ(bigNeg.GetY(), -10287.21);
        EXPECT_FLOAT_EQ(bigNeg.GetZ(), -984.4);
        
        Vector3D mix = Vector3D(-10.0, 29.0, -412.0);
        EXPECT_FLOAT_EQ(mix.GetX(), -10.0);
        EXPECT_FLOAT_EQ(mix.GetY(), 29.0);
        EXPECT_FLOAT_EQ(mix.GetZ(), -412.0);

        
        Vector3D upper = Vector3D(3.4e+38, 3.4e+38, 3.4e+38);
        EXPECT_FLOAT_EQ(upper.GetX(), 3.4e+38);
        EXPECT_FLOAT_EQ(upper.GetY(), 3.4e+38);
        EXPECT_FLOAT_EQ(upper.GetZ(), 3.4e+38);

        Vector3D posMiddle = Vector3D(1.7e+19, 1.7e+19, 1.7e+19);
        EXPECT_FLOAT_EQ(posMiddle.GetX(), 1.7e+19);
        EXPECT_FLOAT_EQ(posMiddle.GetY(), 1.7e+19);
        EXPECT_FLOAT_EQ(posMiddle.GetZ(), 1.7e+19);

        Vector3D negMiddle = Vector3D(-1.7e+19, -1.7e+19, -1.7e+19);
        EXPECT_FLOAT_EQ(negMiddle.GetX(), -1.7e+19);
        EXPECT_FLOAT_EQ(negMiddle.GetY(), -1.7e+19);
        EXPECT_FLOAT_EQ(negMiddle.GetZ(), -1.7e+19);

        Vector3D lower = Vector3D(-3.4e+38, -3.4e+38, -3.4e+38);
        EXPECT_FLOAT_EQ(lower.GetX(), -3.4e+38);
        EXPECT_FLOAT_EQ(lower.GetY(), -3.4e+38);
        EXPECT_FLOAT_EQ(lower.GetZ(), -3.4e+38);
    }


    TEST_F(Vector3D_Test, AssignmentOperator) {
        Vector3D zeroCopy;
        zeroCopy = zero;
        EXPECT_FLOAT_EQ(zeroCopy.GetX(), 0.0);
        EXPECT_FLOAT_EQ(zeroCopy.GetY(), 0.0);
        EXPECT_FLOAT_EQ(zeroCopy.GetZ(), 0.0);

        Vector3D posOneCopy;
        posOneCopy = posOne;
        EXPECT_FLOAT_EQ(posOneCopy.GetX(), 1.0);
        EXPECT_FLOAT_EQ(posOneCopy.GetY(), 1.0);
        EXPECT_FLOAT_EQ(posOneCopy.GetZ(), 1.0);

        Vector3D vecCopy = vec;
        EXPECT_FLOAT_EQ(vecCopy.GetX(), 1.5);
        EXPECT_FLOAT_EQ(vecCopy.GetY(), 30.65);
        EXPECT_FLOAT_EQ(vecCopy.GetZ(), -5.67);
    }

    TEST_F(Vector3D_Test, Addition) {
        Vector3D add1 = zero + posOne;
        EXPECT_FLOAT_EQ(add1.GetX(), 1.0);
        EXPECT_FLOAT_EQ(add1.GetY(), 1.0);
        EXPECT_FLOAT_EQ(add1.GetZ(), 1.0);

        Vector3D add2 = zero + xAxis;
        EXPECT_FLOAT_EQ(add2.GetX(), 1.0);
        EXPECT_FLOAT_EQ(add2.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add2.GetZ(), 0.0);

        Vector3D add3 = zero + yAxis;
        EXPECT_FLOAT_EQ(add3.GetX(), 0.0);
        EXPECT_FLOAT_EQ(add3.GetY(), 1.0);
        EXPECT_FLOAT_EQ(add3.GetZ(), 0.0);

        Vector3D add4 = zero + zAxis;
        EXPECT_FLOAT_EQ(add4.GetX(), 0.0);
        EXPECT_FLOAT_EQ(add4.GetY(), 0.0);
        EXPECT_FLOAT_EQ(add4.GetZ(), 1.0);

        Vector3D add5 = vec + zero;
        EXPECT_FLOAT_EQ(add5.GetX(), 1.5);
        EXPECT_FLOAT_EQ(add5.GetY(), 30.65);
        EXPECT_FLOAT_EQ(add5.GetZ(), -5.67);

        Vector3D add6 = vec + posOne;
        EXPECT_FLOAT_EQ(add6.GetX(), 2.5);
        EXPECT_FLOAT_EQ(add6.GetY(), 31.65);
        EXPECT_FLOAT_EQ(add6.GetZ(), -4.67);

        Vector3D add7 = vec + negOne;
        EXPECT_FLOAT_EQ(add7.GetX(), 0.5);
        EXPECT_FLOAT_EQ(add7.GetY(), 29.65);
        EXPECT_FLOAT_EQ(add7.GetZ(), -6.67);
                               

    }
    TEST_F(Vector3D_Test, Increment) {
        Vector3D v  = Vector3D(); // default values of 0.0 for x,y,z
        v += zero;
        EXPECT_FLOAT_EQ(v.GetX(), 0.0);
        EXPECT_FLOAT_EQ(v.GetY(), 0.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 0.0);

        v += posOne;
        EXPECT_FLOAT_EQ(v.GetX(), 1.0);
        EXPECT_FLOAT_EQ(v.GetY(), 1.0);
        EXPECT_FLOAT_EQ(v.GetZ(), 1.0);

        v += vec;
        EXPECT_FLOAT_EQ(v.GetX(), 2.5);
        EXPECT_FLOAT_EQ(v.GetY(), 31.65);
        EXPECT_FLOAT_EQ(v.GetZ(), -4.67);

        v += negOne;
        EXPECT_FLOAT_EQ(v.GetX(), 1.5);
        EXPECT_FLOAT_EQ(v.GetY(), 30.65);
        EXPECT_FLOAT_EQ(v.GetZ(), -5.67);

        Vector3D thousand = Vector3D(1000.0,1000.0,1000.0);
        v += thousand;
        EXPECT_FLOAT_EQ(v.GetX(), 1001.5);
        EXPECT_FLOAT_EQ(v.GetY(), 1030.65);
        EXPECT_FLOAT_EQ(v.GetZ(), 994.33);

    }

    TEST_F(Vector3D_Test, Subtraction) {
        Vector3D sub1 = zero - posOne;
        EXPECT_FLOAT_EQ(sub1.GetX(), -1.0);
        EXPECT_FLOAT_EQ(sub1.GetY(), -1.0);
        EXPECT_FLOAT_EQ(sub1.GetZ(), -1.0);

        Vector3D sub2 = zero - xAxis;
        EXPECT_FLOAT_EQ(sub2.GetX(), -1.0);
        EXPECT_FLOAT_EQ(sub2.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub2.GetZ(), 0.0);

        Vector3D sub3 = zero - yAxis;
        EXPECT_FLOAT_EQ(sub3.GetX(), 0.0);
        EXPECT_FLOAT_EQ(sub3.GetY(), -1.0);
        EXPECT_FLOAT_EQ(sub3.GetZ(), 0.0);

        Vector3D sub4 = zero - zAxis;
        EXPECT_FLOAT_EQ(sub4.GetX(), 0.0);
        EXPECT_FLOAT_EQ(sub4.GetY(), 0.0);
        EXPECT_FLOAT_EQ(sub4.GetZ(), -1.0);

        Vector3D sub5 = vec - zero;
        EXPECT_FLOAT_EQ(sub5.GetX(), 1.5);
        EXPECT_FLOAT_EQ(sub5.GetY(), 30.65);
        EXPECT_FLOAT_EQ(sub5.GetZ(), -5.67);

        Vector3D sub6 = vec - posOne;
        EXPECT_FLOAT_EQ(sub6.GetX(), 0.5);
        EXPECT_FLOAT_EQ(sub6.GetY(), 29.65);
        EXPECT_FLOAT_EQ(sub6.GetZ(), -6.67);

        Vector3D sub7 = vec - negOne;
        EXPECT_FLOAT_EQ(sub7.GetX(), 2.5);
        EXPECT_FLOAT_EQ(sub7.GetY(), 31.65);
        EXPECT_FLOAT_EQ(sub7.GetZ(), -4.67);

    }
    TEST_F(Vector3D_Test, Decrement) {
        Vector3D v  = Vector3D(); // default values of 0.0 for x,y,z
        v -= posOne;
        EXPECT_FLOAT_EQ(v.GetX(), -1.0);
        EXPECT_FLOAT_EQ(v.GetY(), -1.0);
        EXPECT_FLOAT_EQ(v.GetZ(), -1.0);

        v -= vec;
        EXPECT_FLOAT_EQ(v.GetX(), -2.5);
        EXPECT_FLOAT_EQ(v.GetY(), -31.65);
        EXPECT_FLOAT_EQ(v.GetZ(), 4.67);

        v -= negOne;
        EXPECT_FLOAT_EQ(v.GetX(), -1.5);
        EXPECT_FLOAT_EQ(v.GetY(), -30.65);
        EXPECT_FLOAT_EQ(v.GetZ(), 5.67);

        Vector3D thousand = Vector3D(1000.0,1000.0,1000.0);
        v -= thousand;
        EXPECT_FLOAT_EQ(v.GetX(), -1001.5);
        EXPECT_FLOAT_EQ(v.GetY(), -1030.65);
        EXPECT_FLOAT_EQ(v.GetZ(), -994.33);

    }

    TEST_F(Vector3D_Test, Multiplication) {
        Vector3D multTest = zero * 0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = zero * 8;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = posOne * 1;
        EXPECT_FLOAT_EQ(multTest.GetX(), 1.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 1.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 1.0);

        multTest = posOne * 5;
        EXPECT_FLOAT_EQ(multTest.GetX(), 5.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 5.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 5.0);

        multTest = posOne * -100;
        EXPECT_FLOAT_EQ(multTest.GetX(), -100.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), -100.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -100.0);

        multTest = xAxis * 1;
        EXPECT_FLOAT_EQ(multTest.GetX(), 1.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = yAxis * -1;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), -1.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = negOne * 1;
        EXPECT_FLOAT_EQ(multTest.GetX(), -1.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), -1.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -1.0);

        multTest = negOne * 0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);
        
        multTest = negOne * -0.25;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.25);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.25);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.25);

        multTest = negOne * 14.5;
        EXPECT_FLOAT_EQ(multTest.GetX(), -14.5);
        EXPECT_FLOAT_EQ(multTest.GetY(), -14.5);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -14.5);

    }

    TEST_F(Vector3D_Test, MultiplicationAssignment) {
        Vector3D multTest = Vector3D();
        multTest *= 0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest *= 10.0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 0.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 0.0);

        multTest = Vector3D(1.0,1.0,1.0);
        multTest *= 100.0;
        EXPECT_FLOAT_EQ(multTest.GetX(), 100.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 100.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 100.0);

        multTest *= 0.5;
        EXPECT_FLOAT_EQ(multTest.GetX(), 50.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 50.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 50.0);

        multTest *= -0.1;
        EXPECT_FLOAT_EQ(multTest.GetX(), -5.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), -5.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), -5.0);

        multTest *= -2;
        EXPECT_FLOAT_EQ(multTest.GetX(), 10.0);
        EXPECT_FLOAT_EQ(multTest.GetY(), 10.0);
        EXPECT_FLOAT_EQ(multTest.GetZ(), 10.0);
        

    }

    TEST_F(Vector3D_Test, GetMagnitude) {
        EXPECT_FLOAT_EQ(zero.GetMagnitude(), 0.0);
        EXPECT_FLOAT_EQ(xAxis.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(yAxis.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(zAxis.GetMagnitude(), 1.0);

        EXPECT_FLOAT_EQ(posOne.GetMagnitude(), 1.7320508);
        EXPECT_FLOAT_EQ(negOne.GetMagnitude(), 1.7320508);
        EXPECT_FLOAT_EQ(vec.GetMagnitude(), 31.206112);
    }

    TEST_F(Vector3D_Test, Normalize) {
        zero.Normalize();
        EXPECT_FLOAT_EQ(zero.GetX(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetY(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetZ(), 0.0);
        EXPECT_FLOAT_EQ(zero.GetMagnitude(), 0.0);


        Vector3D v = Vector3D(3.0, 4.0, 1.0);
        v.Normalize();
        EXPECT_FLOAT_EQ(v.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(v.GetX(), 0.58834839);
        EXPECT_FLOAT_EQ(v.GetY(), 0.7844645405);
        EXPECT_FLOAT_EQ(v.GetZ(), 0.1961161351);

        Vector3D one = Vector3D(0.0, 1.0, 0.0);
        one.Normalize();
        EXPECT_FLOAT_EQ(one.GetMagnitude(), 1.0);
        EXPECT_FLOAT_EQ(one.GetX(), 0.0);
        EXPECT_FLOAT_EQ(one.GetY(), 1.0);
        EXPECT_FLOAT_EQ(one.GetZ(), 0.0);

    }

    TEST_F(Vector3D_Test, IsNormalized) {
        EXPECT_EQ(xAxis.IsNormalized(), true);
        EXPECT_EQ(yAxis.IsNormalized(), true);
        EXPECT_EQ(zAxis.IsNormalized(), true);
        
        EXPECT_EQ(zero.IsNormalized(), false);
        EXPECT_EQ(posOne.IsNormalized(), false);
        EXPECT_EQ(vec.IsNormalized(), false);

        Vector3D v = Vector3D(3.0, -5.0, 4.0);
        v.Normalize();
        EXPECT_EQ(v.IsNormalized(), true);

        v = Vector3D(3000000, -4e9, 439);
        v.Normalize();
        EXPECT_EQ(v.IsNormalized(), true);

        v = Vector3D(3, 46.7, -12);
        v.Normalize();
        EXPECT_EQ(v.IsNormalized(), true);
        
    }

    TEST_F(Vector3D_Test, GetDistance) {
        EXPECT_FLOAT_EQ(posOne.GetDistance(zero), 1.7320508);
        EXPECT_FLOAT_EQ(negOne.GetDistance(zero), 1.7320508);

        EXPECT_FLOAT_EQ(xAxis.GetDistance(zero), 1.0);
        EXPECT_FLOAT_EQ(yAxis.GetDistance(zero), 1.0);
        EXPECT_FLOAT_EQ(zAxis.GetDistance(zero), 1.0);

        EXPECT_FLOAT_EQ(vec.GetDistance(zero), vec.GetMagnitude());

        Vector3D copyOne = Vector3D();
        copyOne = posOne;
        EXPECT_FLOAT_EQ(copyOne.GetDistance(posOne), 0.0);
        
    }
    
    TEST_F(Vector3D_Test, GetVector) {
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

        v = yAxis.GetVector();
        ASSERT_EQ(v.size(), 3) << "Vectors are unequal length";
        EXPECT_EQ(v.at(0), yAxis.GetX());
        EXPECT_EQ(v.at(1), yAxis.GetY());
        EXPECT_EQ(v.at(2), yAxis.GetZ());

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
    

    TEST_F(Vector3D_Test, Display) {
        std::string expected_out_1 = "(0.000, 0.000, 0.000)\n";
        std::string expected_out_2 = "(1.000, 0.000, 0.000)\n";
        std::string expected_out_3 = "(0.000, 1.000, 0.000)\n";
        std::string expected_out_4 = "(0.000, 0.000, 1.000)\n";
        std::string expected_out_5 = "(1.000, 1.000, 1.000)\n";
        std::string expected_out_6 = "(-1.000, -1.000, -1.000)\n";
        std::string expected_out_7 = "(1.500, 30.650, -5.670)\n";
  
        testing::internal::CaptureStdout();
        zero.Display();
        std::string output1 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout(); 
        xAxis.Display();
        std::string output2 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout();
        yAxis.Display();
        std::string output3 = testing::internal::GetCapturedStdout();

        testing::internal::CaptureStdout();
        zAxis.Display();
        std::string output4 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout(); 
        posOne.Display();
        std::string output5 = testing::internal::GetCapturedStdout();
  
        testing::internal::CaptureStdout();
        negOne.Display();
        std::string output6 = testing::internal::GetCapturedStdout();

        testing::internal::CaptureStdout();
        vec.Display();
        std::string output7 = testing::internal::GetCapturedStdout();
  
        EXPECT_EQ(output1, expected_out_1);
        EXPECT_EQ(output2, expected_out_2);
        EXPECT_EQ(output3, expected_out_3);
        EXPECT_EQ(output4, expected_out_4);
        EXPECT_EQ(output5, expected_out_5);
        EXPECT_EQ(output6, expected_out_6);
        EXPECT_EQ(output7, expected_out_7);
        

    };

}