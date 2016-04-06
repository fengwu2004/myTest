//
//  BeaconSourceMgr.m
//  TestBeacon
//
//  Created by ky on 16/4/6.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "BeaconSourceMgr.h"


@interface BeaconSourceMgr()

@property (nonatomic, retain) NSArray *beaconSource;

@end

@implementation BeaconSourceMgr

+ (instancetype)sharedInstance {
    
    static BeaconSourceMgr *_instance;
    
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        
        _instance = [[BeaconSourceMgr alloc] init];
    });
    
    return _instance;
}

- (id)init {
    
    self = [super init];
    
    if (self) {
        
        NSDictionary *dic0 = @{@"regionuuid":@"FDA50693-A4E2-4FB1-AFCF-C6EB07647825",
                               @"beaconItem":@"beacon_tingchechang",
                               @"title":@"sensoro停车场1"};
        
        NSDictionary *dic1 = @{@"regionuuid":@"E3879308-4FA3-4F30-AC22-19ECDCB0D8C8",
                               @"beaconItem":@"beacon_tingchechang",
                               @"title":@"寻息停车场2"};
        
        NSDictionary *dic2 = @{@"regionuuid":@"E2879308-4FA3-4F30-AC22-19ECDCB0D8C8",
                               @"beaconItem":@"beacon_tingchechang",
                               @"title":@"四月兄弟停车场3"};
        
        NSDictionary *dic3 = @{@"regionuuid":@"E2C56DB5-DFFB-48D2-B060-D0F5A71096E0",
                               @"beaconItem":@"beacon_1031",
                               @"title":@"办公室"};
        
        _beaconSource = @[dic0, dic1, dic2, dic3];
    }
    
    _selectIndex = 0;
    
    return self;
}

- (NSInteger)totalCount {
    
    return [_beaconSource count];
}

- (NSString*)getBeaconUUID {
    
    if (_selectIndex >= _beaconSource.count) {
        
        return @"";
    }
    
    return [_beaconSource[_selectIndex] objectForKey:@"regionuuid"];
}

- (NSString*)getBeaconItmes {
    
    if (_selectIndex >= _beaconSource.count) {
        
        return @"";
    }
    
    return [_beaconSource[_selectIndex] objectForKey:@"beaconItem"];
}

- (NSString*)getBeaconTitle:(NSInteger)nIndex {
    
    if (nIndex >= _beaconSource.count) {
        
        return @"";
    }
    
    return [_beaconSource[nIndex] objectForKey:@"title"];
}

@end
