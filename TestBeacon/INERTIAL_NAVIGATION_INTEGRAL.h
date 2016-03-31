//
//  INERTIAL_NAVIGATION_INTEGRAL.h
//  CloudAtlasTestProject
//
//  Created by 卢毅 on 16/1/11.
//  Copyright © 2016年 innerpeacer. All rights reserved.
//

#ifndef INERTIAL_NAVIGATION_INTEGRAL_h
#define INERTIAL_NAVIGATION_INTEGRAL_h

#include <math.h>
#include <utility>
//#define PI 3.1415926535898;

struct location
{//当前位置,三个方向,m为单位
    double x;double y; double z;
};

struct accelerated_speed
{//加速度,三个方向,m/(s^2)
    double xa;double ya; double za;
};

struct speed
{//速度,三个方向，m/s
    double vx;double vy; double vz; int step;
};

struct angle
{//角度，单位为弧度（手机与平面坐标系的夹角）
    double angle_x;double angle_y;double angle_z;
};

class INERTIAL_NAVIGATION_INTEGRAL
{
public:
    INERTIAL_NAVIGATION_INTEGRAL();
    std::pair<location,speed> integral(location initial_location, accelerated_speed aspeed, angle initial_angle, double magneticHeading, speed initial_speed);
};

#endif /* INERTIAL_NAVIGATION_INTEGRAL_h */
