//
//  YFBeaconDataCollecter.h
//  YFBeaconDataCollecter
//
//  Created by ky on 16/3/30.
//  Copyright © 2016年 ky. All rights reserved.

#import <Foundation/Foundation.h>
/*
 YFBeaconSteamCollecter
 
 说明：蓝牙发射器数据采集
 */

class YFBeaconDataProcesser;

@interface YFBeaconDataCollecter : NSObject {
    
@private
    YFBeaconDataProcesser *beaconProcesser;
}

+ (instancetype)sharedInstance;

- (void)setBeaconProcesser:(YFBeaconDataProcesser*)processer;

@end
