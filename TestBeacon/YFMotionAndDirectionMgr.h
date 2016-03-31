//
//  YFMotionAndDirectionMgr.h
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMotion/CoreMotion.h>

@interface YFMotionAndDirectionMgr : NSObject

+ (instancetype)sharedInstance;

@property (nonatomic, assign) double roll;
@property (nonatomic, assign) double pitch;
@property (nonatomic, assign) double yaw;
@property (nonatomic, assign) CMAcceleration acceleration;
@property (nonatomic, assign) double direction;

@end
