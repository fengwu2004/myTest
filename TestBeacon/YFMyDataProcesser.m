//
//  YFMyDataProcesser.cpp
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#include "YFMyDataProcesser.h"
#include "TriLoaction.h"
#import "StoreMgr.h"
#import "YFMotionAndDirectionMgr.h"

MyDataProcesser::MyDataProcesser(const std::vector<YFBeaconEmitter>& allEmitters):YFBeaconDataProcesser(allEmitters) {
    
    m_pLocationProcesser = new CTriLoaction;
    
    m_pNaviProcesser = new INERTIAL_NAVIGATION_INTEGRAL;
}

void MyDataProcesser::ProcessData(const std::vector<BEACON_VALUE> &alldata) {
    
    size_t size = alldata.size();
    
    BEACON_VALUE *data = new BEACON_VALUE[size];
    
    for (int i = 0; i < size; ++i) {
        
        data[i] = alldata[i];
    }
    
    m_pLocationProcesser->SetScanning((int)size, data);
}

void MyDataProcesser::OnNaviProcess() {
    
    accelerated_speed aspeed;
    
    aspeed.xa = [YFMotionAndDirectionMgr sharedInstance].acceleration.x;
    
    aspeed.ya = [YFMotionAndDirectionMgr sharedInstance].acceleration.y;
    
    aspeed.za = [YFMotionAndDirectionMgr sharedInstance].acceleration.z;
    
    angle initial_angle;
    
    initial_angle.angle_x = [YFMotionAndDirectionMgr sharedInstance].pitch;
    
    initial_angle.angle_y = [YFMotionAndDirectionMgr sharedInstance].yaw;
    
    initial_angle.angle_z = [YFMotionAndDirectionMgr sharedInstance].roll;
    
    double dir = [YFMotionAndDirectionMgr sharedInstance].direction;
    
    std::pair<location, speed> resultLoc = m_pNaviProcesser->integral(m_loc, aspeed, initial_angle, dir, m_speed);
    
    m_speed = resultLoc.second;
    
    m_loc = resultLoc.first;
}

bool MyDataProcesser::CheckAndGetOutput(double& x, double& y) {
    
    bool result = m_pLocationProcesser->Location(&x, &y);
    
    if (result) {
        
        m_loc.x = x; m_loc.y = y; m_loc.z = 0;
        
        m_speed.vx = m_speed.vy = m_speed.vz = 0;
        
        m_speed.step = 0;
        
        return true;
    }
    
    return false;
}