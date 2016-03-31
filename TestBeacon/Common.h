//
//  Common.h
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#ifndef Common_h
#define Common_h

struct BEACON_VALUE {
    
    unsigned int time;//当前时间千分之一秒
    std::string ID;//beacon标识
    double x;
    double y;
    double r;
    double A;
    double M; //距离
    bool bM; //距离标志
};

struct YFBeaconEmitter {
    
    std::string strId;
    double x;
    double y;
};


#endif /* Common_h */
