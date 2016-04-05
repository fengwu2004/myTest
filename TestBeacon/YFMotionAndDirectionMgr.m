//
//  YFMotionAndDirectionMgr.m
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "YFMotionAndDirectionMgr.h"

static const NSTimeInterval delta = 0.02;

@interface YFMotionAndDirectionMgr()

@property (nonatomic, retain) CMMotionManager *motionManager;
@property (nonatomic, retain) NSTimer *monitorTimer;

@end

@implementation YFMotionAndDirectionMgr

+ (instancetype)sharedInstance {
    
    static YFMotionAndDirectionMgr *_instance;
    
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        
        _instance = [[YFMotionAndDirectionMgr alloc] init];
    });
    
    return _instance;
}

- (id)init {
    
    self = [super init];
    
    if (self) {
        
        [self setupMotionAndMonitor];
    }
    
    return self;
}

- (void)setupMotionAndMonitor {
    
    _motionManager = [[CMMotionManager alloc] init];
    
    [_motionManager startGyroUpdates];
    
    [_motionManager startDeviceMotionUpdates];
    
    [_motionManager startAccelerometerUpdates];
    
    [_motionManager setGyroUpdateInterval:delta];
    
    [_motionManager setAccelerometerUpdateInterval:delta];
    
    [_motionManager setDeviceMotionUpdateInterval:delta];
    
    _monitorTimer = [NSTimer scheduledTimerWithTimeInterval:delta target:self selector:@selector(onMotionUpdate:) userInfo:nil repeats:YES];
}

- (void)onMotionUpdate:(id)sender {
    
    _acceleration = _motionManager.deviceMotion.userAcceleration;
    
    _roll = _motionManager.deviceMotion.attitude.roll;
    
    _pitch = _motionManager.deviceMotion.attitude.pitch;
    
    _yaw = _motionManager.deviceMotion.attitude.yaw;
}

@end
