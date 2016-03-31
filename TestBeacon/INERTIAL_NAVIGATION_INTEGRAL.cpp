//
//  INERTIAL_NAVIGATION_INTEGRAL.cpp
//  CloudAtlasTestProject
//
//  Created by 卢毅 on 16/1/21.
//  Copyright © 2016年 innerpeacer. All rights reserved.
//

#include "INERTIAL_NAVIGATION_INTEGRAL.h"
#include <stdio.h>
#include <math.h>

INERTIAL_NAVIGATION_INTEGRAL::INERTIAL_NAVIGATION_INTEGRAL(){};

speed initial_speed={0.0,0.0,0.0,0};//定义初始速度为零

std::pair<location,speed> INERTIAL_NAVIGATION_INTEGRAL::integral(location initial_location, accelerated_speed aspeed, angle initial_angle, double magneticHeading, speed initial_speed)
{//积分计算当前速度，输入项为当前位置，当前加速度(手机坐标系)，当前速度(地面坐标系，默认0)，计算的间隔时间(默认0.1秒)
    
//    aspeed.xa=int(aspeed.xa*100.0)/100.0;
//    aspeed.ya=int(aspeed.ya*100.0)/100.0;
//    aspeed.za=int(aspeed.za*100.0)/100.0;
//    if(aspeed.xa*aspeed.xa+aspeed.ya*aspeed.ya+aspeed.za*aspeed.za>=6)
//    {
//        aspeed.xa=0.0,aspeed.ya=0.0,aspeed.za=0.0;
//    }
//    
//    if (aspeed.xa==0 && aspeed.ya==0 && aspeed.za*100==0)
//    {
//        return std::make_pair(initial_location,initial_speed);
//    }
//    else
//    {
    
    if (int(aspeed.xa*100.0)/100.0==0 && int(aspeed.ya*100.0)/100.0==0 && int(aspeed.za*100.0)/100.0==0)
    {
        return std::make_pair(initial_location,initial_speed);
    }
    else
    {
        int interval=200;
        //定义从地面坐标系到手机坐标系的旋转矩阵
//        double a1,a2,a3,b1,b2,b3,c1,c2,c3;
//        a1=cos(initial_angle.angle_y)*cos(initial_angle.angle_z)-sin(initial_angle.angle_x)*sin(initial_angle.angle_y)*sin(initial_angle.angle_z);
//        a2=-cos(initial_angle.angle_y)*sin(initial_angle.angle_z)-sin(initial_angle.angle_x)*sin(initial_angle.angle_y)*cos(initial_angle.angle_z);
//        a3=-sin(initial_angle.angle_y)*cos(initial_angle.angle_x);
//        b1=cos(initial_angle.angle_x)*sin(initial_angle.angle_z);
//        b2=cos(initial_angle.angle_x)*cos(initial_angle.angle_z);
//        b3=-sin(initial_angle.angle_x);
//        c1=sin(initial_angle.angle_y)*cos(initial_angle.angle_z)+cos(initial_angle.angle_y)*sin(initial_angle.angle_x)*sin(initial_angle.angle_z);
//        c2=-sin(initial_angle.angle_y)*sin(initial_angle.angle_z)+cos(initial_angle.angle_y)*sin(initial_angle.angle_x)*cos(initial_angle.angle_z);
//        c3=cos(initial_angle.angle_y)*cos(initial_angle.angle_x);
//        //定义从手机水平坐标系到地理坐标系的旋转矩阵
//        double aa1,aa2,bb1,bb2;
//        aa1=cos(magneticHeading);aa2=-sin(magneticHeading);
//        bb1=sin(magneticHeading);bb2=cos(magneticHeading);
//        
//        speed phone_speed;
//        //将vx和vy换到手机水平坐标系
//        //乘以二维旋转矩阵的逆阵
//        //旋转矩阵为正交阵，求逆等于其转置
//        double vx_horizontal=initial_speed.vx*aa1+initial_speed.vy*bb1;
//        double vy_horizontal=initial_speed.vx*aa2+initial_speed.vy*bb1;
//        
//        //再将速度换算到手机坐标系
//        phone_speed.vx=vx_horizontal*a1+vy_horizontal*a2+initial_speed.vz*a3;
//        phone_speed.vy=vx_horizontal*b1+vy_horizontal*b2+initial_speed.vz*b3;
//        phone_speed.vz=vx_horizontal*c1+vy_horizontal*c2+initial_speed.vz*c3;
//        
//        //得到这段时间内的平均速度（手机坐标系）
//        speed v_average;
//        v_average.vx=phone_speed.vx+aspeed.xa*interval/1000/2;//得到当前时间段内的平均速度
//        v_average.vy=phone_speed.vy+aspeed.ya*interval/1000/2;
//        v_average.vz=phone_speed.vz+aspeed.za*interval/1000/2;
//        
//        //得到手机坐标系三个方向上的位移
//        double phone_dx=v_average.vx*interval/1000;
//        double phone_dy=v_average.vy*interval/1000;
//        double phone_dz=v_average.vz*interval/1000;
//        
//        //得到这段时间内手机标系的速度增加值
//        double phone_dvx=aspeed.xa*interval/1000;
//        double phone_dvy=aspeed.ya*interval/1000;
//        double phone_dvz=aspeed.za*interval/1000;
//        
//        //将位移和速度增加值由手机坐标系转回手机水平坐标系
//        //旋转矩阵为正交阵，求逆等于其转置
//        double dx=a1*phone_dx+b1*phone_dy+c1*phone_dz;
//        double dy=a2*phone_dx+b2*phone_dy+c2*phone_dz;
//        double dz=a3*phone_dx+b3*phone_dy+c3*phone_dz;
//        double dvx=a1*phone_dvx+b1*phone_dvy+c1*phone_dvz;
//        double dvy=a2*phone_dvx+b2*phone_dvy+c2*phone_dvz;
//        double dvz=a3*phone_dvx+b3*phone_dvy+c3*phone_dvz;
//        
//        
//        //将手机的水平坐标系(是手机坐标系归算到水平面后的坐标)和磁北方向做转换
//        //手机的水平坐标系和当前地理坐标系转换需要一个旋转角
//        //一般城市坐标都以北方向为y方向(高斯克里格投影)
//        //这样的话可以在地图上画出真的位移
//        double dx_local=dx*aa1+dy*aa2;
//        double dy_local=dx*bb1+dy*bb2;
//        double dvx_local=dvx*aa1+dvy*aa2;
//        double dvy_local=dvx*bb1+dvy*bb2;
//        
//        //求出最后地面上的速度和位移
//        location end_location; speed end_v;
//        end_location.x=initial_location.x+dx_local;
//        end_location.y=initial_location.y+dy_local;
//        end_location.z=initial_location.z+dz;
//        end_v.vx=initial_speed.vx+dvx_local;
//        end_v.vy=initial_speed.vy+dvy_local;
//        end_v.vz=initial_speed.vz+dvz;
        
        double aa1,aa2,bb1,bb2;
        aa1=cos(magneticHeading);aa2=-sin(magneticHeading);
        bb1=sin(magneticHeading);bb2=cos(magneticHeading);
        
        //得到手机坐标系三个方向上的位移
        double local_dx=0,local_dy=0,local_dz=0;
        double aspeed_total=sqrt((aspeed.xa*aspeed.xa+aspeed.ya*aspeed.ya+aspeed.za*aspeed.za));
        if(aspeed_total>(0.01) && aspeed_total<(0.3) )
        {
            //aspeed_total=aspeed_total*1.8/0.1*0.1;
            aspeed_total=0.08/0.1*0.1;
            local_dx=aspeed_total*sin(magneticHeading-M_PI/2);
            local_dy=aspeed_total*cos(magneticHeading-M_PI/2);
            //local_dz=phone_aspeedz_horizontal/0.12*0.1;
        }

        //求出最后地面上的位移
        location end_location;
        end_location.x=initial_location.x+local_dx;
        end_location.y=initial_location.y+local_dy;
        end_location.z=initial_location.z+local_dz;
        
        speed end_v;
        end_v.step = 1;
        
        //返回最后的位置和速度
        //注意返回值是地面坐标系的
        return std::make_pair(end_location,end_v);
    }
}