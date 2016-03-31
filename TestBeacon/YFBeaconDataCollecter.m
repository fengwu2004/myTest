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

#define regionuuid @"FDA50693-A4E2-4FB1-AFCF-C6EB07647825"

@interface YFBeaconDataCollecter()<CLLocationManagerDelegate>

@property (nonatomic, retain) CLLocationManager * locationManager;
@property (nonatomic, retain) NSMutableDictionary *allEmitters;
@property (nonatomic, retain) CLBeaconRegion *beaconRegion;

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
    
    beaconProcesser = nil;
    
    _locationManager = [[CLLocationManager alloc] init];
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        [_locationManager requestWhenInUseAuthorization];
        
        [_locationManager requestAlwaysAuthorization];
    }
    
    [_locationManager setDelegate:self];
    
    [_locationManager setDesiredAccuracy:kCLLocationAccuracyBest];

    _allEmitters = [[NSMutableDictionary alloc] init];
    
    return self;
}

- (void)stop {
    
    if (_beaconRegion) {
        
        [_locationManager stopMonitoringForRegion:_beaconRegion];
        
        [_locationManager stopRangingBeaconsInRegion:_beaconRegion];
    }
}

- (void)testDB {
    
    std::vector<BEACON_VALUE> allData;
    
    for (int i = 0; i < 3; ++i) {
        
        BEACON_VALUE a;
        
        a.time = 100;
        
        a.ID = "13234";
        
        a.x = 100;
        
        a.y = 100;
        
        a.r = 10;
        
        a.M = i;
        
        a.bM = true;
        
        allData.push_back(a);
    }
    
    saveToDB(allData);
}

- (void)setBeaconProcesser:(YFBeaconDataProcesser*)processer {
    
    beaconProcesser = processer;
    
    [self stop];
    
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:regionuuid];
    
    _beaconRegion = [[CLBeaconRegion alloc] initWithProximityUUID:uuid identifier:@""];
    
    [_locationManager startRangingBeaconsInRegion:_beaconRegion];
    
    [_locationManager startMonitoringForRegion:_beaconRegion];
}

#pragma mark --CLLocationManagerDelegate
-(void)locationManager:(CLLocationManager*)manager didRangeBeacons:(NSArray*)beacons inRegion:(CLBeaconRegion*)region {

    std::vector<BEACON_VALUE> allData;
    
    for (CLBeacon *beacon in beacons) {
        
        std::string strId = beaconMinor([beacon.minor doubleValue]);
        
        double x = 0, y = 0;
        
        if (beaconProcesser->GetPos(strId, x, y)) {
            
            allData.push_back(dataAdapter(beacon, x, y));
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

BEACON_VALUE dataAdapter(CLBeacon* beacon, double x, double y) {
    
    BEACON_VALUE data;
    
    data.ID =  beaconMinor([beacon.minor doubleValue]);
    
    data.x = x;
    
    data.y = y;
    
    data.r = beacon.rssi;
    
    data.M = beacon.accuracy;
    
    data.bM = true;
    
    return data;
}

@end
