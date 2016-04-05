//
//  YFBeaconData.h
//  YFBeaconStreamCollecter
//
//  Created by ky on 16/3/30.
//  Copyright © 2016年 ky. All rights reserved.
//

#ifndef YFBeaconData_h
#define YFBeaconData_h

#include <string>
#include <vector>
#include <map>
#include "Common.h"

//#define regionuuid @"FDA50693-A4E2-4FB1-AFCF-C6EB07647825"
//#define beaconSource @"beacon_tingchechang"

#define regionuuid @"E2C56DB5-DFFB-48D2-B060-D0F5A71096E0"
#define beaconSource @"beacon_1031"

class YFBeaconDataProcesser {
    
public:
    YFBeaconDataProcesser(const std::vector<YFBeaconEmitter>& allEmitters);
    
    void run();
    
    virtual ~YFBeaconDataProcesser() {}
    
    virtual void ProcessData(const std::vector<BEACON_VALUE>& alldata) = 0;
    
    virtual bool CheckAndGetOutput(double& x, double& y) = 0;
    
    virtual void OnNaviProcess() = 0;
    
    bool GetPos(const std::string& strId, double& x, double& y);
    
private:
    std::map<std::string, YFBeaconEmitter> m_allEmitters;
    
    bool m_bRunning;
};

#endif /* YFBeaconData_h */
