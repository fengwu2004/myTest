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

class CTriLoaction;

class MyDataProcesser: public YFBeaconDataProcesser {
    
public:
    MyDataProcesser(const std::vector<YFBeaconEmitter>& allEmitters);
    
    virtual void ProcessData(const std::vector<BEACON_VALUE>& alldata);
    
    virtual bool CheckAndGetOutput(double& x, double& y);
    
private:
    CTriLoaction *pLocationProcesser;
};

#endif /* YFMyDataProcesser_hpp */
