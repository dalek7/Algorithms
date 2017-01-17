//
//  SimpleTest.h
//  SophusTest
//
//  Created by Seung-Chan Kim on 1/1/17.
//  Copyright (c) 2017 Seung-Chan Kim. All rights reserved.
//  written for understanding Lie Algebra

#ifndef Sophus_SimpleTest_h
#define Sophus_SimpleTest_h


#include "Thirdparty/sophus/sim3.hpp"
#include "Thirdparty/sophus/se3.hpp"
using namespace Sophus;
using namespace Eigen;
using namespace std;

// Taken from LSD-SLAM
// Typedef and conversion macro for Eigen matrices to currently used type.
// NOTE: a "no-op conversion" is free in terms of performance, as it should be compiled out.
#ifdef SOPHUS_USE_FLOAT
typedef Sophus::SE3f SE3;
typedef Sophus::Sim3f Sim3;
typedef Sophus::SO3f SO3;
#define toSophus(x) ((x).cast<float>())
#define sophusType float
#else
//	typedef Sophus::Vector3d Vector3;
//	typedef Sophus::Vector4d Vector4;
//	typedef Sophus::Vector6d Vector6;
//	typedef Sophus::Vector7d Vector7;
//	typedef Sophus::Quaterniond Quaternion;
typedef Sophus::SE3d SE3;
typedef Sophus::Sim3d Sim3;
typedef Sophus::SO3d SO3;
#define toSophus(x) ((x).cast<double>())
#define sophusType double
#endif


namespace lsd_slam
{
    
inline Sim3 sim3FromSE3(const SE3& se3, sophusType scale)
{
    Sim3 result(se3.unit_quaternion(), se3.translation());
    result.setScale(scale);
    return result;
}

inline SE3 se3FromSim3(const Sim3& sim3)
{
    return SE3(sim3.quaternion(), sim3.translation());
}


    
}


typedef Sophus::SO3d::Point Point;
typedef Sophus::SO3d::Tangent Tangent;

/* 
 in class SO3GroupBase :
 // Group transformations are 3x3 matrices.
 static const int N = 3;
 typedef Eigen::Matrix<Scalar, N, N> Transformation;
 typedef Eigen::Matrix<Scalar, 3, 1> Point;
 typedef Eigen::Matrix<Scalar, DoF, 1> Tangent;
 typedef Eigen::Matrix<Scalar, DoF, DoF> Adjoint;
 
*/

static void test1()
{
    
    //SO3 disturbance = SO3::exp(Sophus::Vector3d(0.05,0,0));
    Point omega1 = Point(0.05,0,0);
    SO3 disturbance = SO3::exp(omega1);
    
    cout << omega1.transpose() << endl;;
    cout << disturbance.matrix() << endl;
    cout << disturbance.log().transpose() << endl;
    
    cout << "==============================" << endl;
    
    Tangent omega2 = Tangent(0.05,0,0);
    disturbance = SO3::exp(omega2);
    
    cout << omega2.transpose() << endl;;
    cout << disturbance.matrix() << endl;
    cout << disturbance.log().transpose() << endl;
    cout << "==============================" << endl;
}

static void test2()
{
    Point omega1 =Point(0.05,0,0);
    SO3 disturbance1 = SO3::exp(omega1);
    
    Point omega2 =Point(0.02,0,0);
    SO3 disturbance2 = SO3::exp(omega2);
    
    
    SO3 disturbance12 = SO3::exp(omega1+omega2);
    SO3 disturbance1x2 = disturbance1 * disturbance2;
    
    cout << (omega1+omega2).transpose() << endl;;
    cout << disturbance12.matrix() << endl;
    cout << disturbance12.log().transpose() << endl;
    cout << disturbance1x2.log().transpose() << endl;

    cout << "==============================" << endl;
}

static void test3()
{
    
    Point omega1 =Point(0.7071, 0.7071, 1.0);
    //double theta1 = std::sqrt(omega1.dot(omega1));
    double theta1 = sqrt(omega1.squaredNorm());
    cout << theta1 << endl;;
    
    SO3 s1 = SO3::exp(omega1);
    
}

#endif
