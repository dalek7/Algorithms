#ifndef COMMON_H
#define COMMON_H

// pcl
#include <pcl/io/pcd_io.h>
#include <pcl/console/print.h>

#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
//#include <pcl_ros/transforms.h>



#define SQR(X)  ((X)*(X))
//#define pi 3.141592


// Useful macros
#define FPS_CALC(_WHAT_) \
    do \
{ \
    static unsigned count = 0;\
    static double last = pcl::getTime ();\
    double now = pcl::getTime (); \
    ++count; \
    if (now - last >= 1.0) \
{ \
    ROS_INFO("FPS of %s: %f", _WHAT_, double(count)/double(now - last)); \
    count = 0; \
    last = now; \
    } \
    }while(false)

#endif // COMMON_H
