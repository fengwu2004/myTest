//
//  YFBeaconDataCollecter.m
//  YFBeaconDataCollecter
//
//  Created by ky on 16/3/30.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "YFBeaconDataCollecter.h"
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#include "YFBeaconData.h"
#include <sstream>
#import "StoreMgr.h"
#import "BeaconRaw.h"
#import "YFMotionAndDirectionMgr.h"
#import "BeaconSourceMgr.h"

@interface YFBeaconDataCollecter()<CLLocationManagerDelegate>

@property (nonatomic, retain) CLLocationManager * locationManager;
@property (nonatomic, retain) NSMutableDictionary *allEmitters;
@property (nonatomic, retain) CLBeaconRegion *beaconRegion;
@property (nonatomic, retain) NSDate *startDate;

@end

@implementation YFBeaconDataCollecter

+ (instancetype)sharedInstance {
    
    static YFBeaconDataCollecter *_instance;
    
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        
        _instance = [[YFBeaconDataCollecter alloc] init];
    });
    
    return _instance;
}

- (instancetype)init {
    
    self = [super init];
    
    if (!self) {
        
        return nil;
    }
    
    _startDate = [NSDate date];
    
    beaconProcesser = nil;
    
    _locationManager = [[CLLocationManager alloc] init];
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        [_locationManager requestWhenInUseAuthorization];
        
        [_locationManager requestAlwaysAuthorization];
    }
    
    [_locationManager setDelegate:self];
    
    [_locationManager setDesiredAccuracy:kCLLocationAccuracyBest];
    
    [_locationManager startUpdatingHeading];

    _allEmitters = [[NSMutableDictionary alloc] init];
    
    return self;
}

- (void)stop {
    
    if (_beaconRegion) {
        
        [_locationManager stopMonitoringForRegion:_beaconRegion];
        
        [_locationManager stopRangingBeaconsInRegion:_beaconRegion];
    }
}

- (void)setBeaconProcesser:(YFBeaconDataProcesser*)processer {
    
    beaconProcesser = processer;
    
    [self stop];
    
    NSString *beaconUUID = [[BeaconSourceMgr sharedInstance] getBeaconUUID];
    
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:beaconUUID];
    
    _beaconRegion = [[CLBeaconRegion alloc] initWithProximityUUID:uuid identifier:@""];
    
    [_locationManager startRangingBeaconsInRegion:_beaconRegion];
    
    [_locationManager startMonitoringForRegion:_beaconRegion];
}

#pragma mark --CLLocationManagerDelegate
-(void)locationManager:(CLLocationManager*)manager didRangeBeacons:(NSArray*)beacons inRegion:(CLBeaconRegion*)region {

    unsigned int time = [[NSDate date] timeIntervalSinceDate:_startDate] * 1000;
    
    std::vector<BEACON_VALUE> allData;
    
    for (CLBeacon *beacon in beacons) {
        
        std::string strId = beaconMinor([beacon.minor doubleValue]);
        
        double x = 0, y = 0;
        
        if (beaconProcesser->GetPos(strId, x, y)) {
            
            allData.push_back(dataAdapter(beacon, time, x, y));
        }
    }
    
    if (beaconProcesser) {
        
        beaconProcesser->ProcessData(allData);
    }
    
    saveToDB(allData);
}

-(void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading{
    
    [YFMotionAndDirectionMgr sharedInstance].direction = ((newHeading.trueHeading > 0) ? newHeading.trueHeading : newHeading.magneticHeading);
}

void saveToDB(const std::vector<BEACON_VALUE>& allData) {
    
    NSMutableArray *array = [[NSMutableArray alloc] init];
    
    for (std::vector<BEACON_VALUE>::const_iterator iter = allData.begin(); iter != allData.end(); ++iter) {
        
        BeaconRaw *raw = [[BeaconRaw alloc] init];
        
        raw.time = [NSNumber numberWithInteger:iter->time];
        
        std::string minor = iter->ID;
        
        raw.minor = [NSString stringWithCString:minor.c_str() encoding:NSUTF8StringEncoding];
        
        raw.x = [NSNumber numberWithDouble:iter->x];
        
        raw.y = [NSNumber numberWithDouble:iter->y];
        
        raw.r = [NSNumber numberWithDouble:iter->r];
        
        raw.M = [NSNumber numberWithDouble:iter->M];
        
        [array addObject:raw];
    }
    
    [[StoreMgr sharedInstance] saveBeacon:[array copy]];
}

std::string beaconMinor(double minor) {
    
    std::stringstream minorStream;
    
    minorStream << minor;
    
    return minorStream.str();
}

BEACON_VALUE dataAdapter(CLBeacon* beacon, unsigned int time, double x, double y) {
    
    BEACON_VALUE data;
    
    data.ID =  beaconMinor([beacon.minor doubleValue]);
    
    data.time = time;
    
    data.x = x;
    
    data.y = y;
    
    data.r = beacon.rssi;
    
    data.M = beacon.accuracy;
    
    data.bM = true;
    
    return data;
}

@end
