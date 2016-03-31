//
//  YFBeaconData.m
//  YFBeaconStreamCollecter
//
//  Created by ky on 16/3/30.
//  Copyright © 2016年 ky. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "YFBeaconData.h"
#import "YFBeaconDataCollecter.h"

YFBeaconDataProcesser::YFBeaconDataProcesser(const std::vector<YFBeaconEmitter>& allEmitters) {
    
    for (std::vector<YFBeaconEmitter>::const_iterator iter = allEmitters.begin(); iter != allEmitters.end(); ++iter) {
        
        m_allEmitters[iter->strId] = *iter;
    }
    
    m_bRunning = false;
}

void YFBeaconDataProcesser::run() {
    
    if (!m_bRunning) {
        
        [[YFBeaconDataCollecter sharedInstance] setBeaconProcesser:this];
    }
}

bool YFBeaconDataProcesser::GetPos(const std::string& strId, double& x, double& y) {
    
    if (m_allEmitters.count(strId) <= 0) {
        
        return false;
    }
    
    x = m_allEmitters[strId].x;
    
    y = m_allEmitters[strId].y;
    
    return true;
}

