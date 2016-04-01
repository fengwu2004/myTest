//
//  YFMyDataProcesser.hpp
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#ifndef YFMyDataProcesser_hpp
#define YFMyDataProcesser_hpp

#include <stdio.h>
#include "YFBeaconData.h"
#include "INERTIAL_NAVIGATION_INTEGRAL.h"

class CTriLoaction;

class MyDataProcesser: public YFBeaconDataProcesser {
    
public:
    MyDataProcesser(const std::vector<YFBeaconEmitter>& allEmitters);
    
    virtual void ProcessData(const std::vector<BEACON_VALUE>& alldata);
    
    virtual bool CheckAndGetOutput(double& x, double& y);
    
    virtual void OnNaviProcess();
    
    location Result() { return m_loc; }
    
private:
    CTriLoaction *m_pLocationProcesser;
    
    speed m_speed;
    
    location m_loc;
    
    INERTIAL_NAVIGATION_INTEGRAL *m_pNaviProcesser;
};

#endif /* YFMyDataProcesser_hpp */
