//
//  YFMyDataProcesser.cpp
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#include "YFMyDataProcesser.hpp"
#include "TriLoaction.h"

MyDataProcesser::MyDataProcesser(const std::vector<YFBeaconEmitter>& allEmitters):YFBeaconDataProcesser(allEmitters) {
    
    pLocationProcesser = new CTriLoaction;
}

void MyDataProcesser::ProcessData(const std::vector<BEACON_VALUE> &alldata) {
    
    size_t size = alldata.size();
    
    BEACON_VALUE *data = new BEACON_VALUE[size];
    
    for (int i = 0; i < size; ++i) {
        
        data[i] = alldata[i];
    }
    
    pLocationProcesser->SetScanning((int)size, data);
}