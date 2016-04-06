//
//  BeaconSourceMgr.h
//  TestBeacon
//
//  Created by ky on 16/4/6.
//  Copyright © 2016年 ky. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeaconSourceMgr : NSObject

@property (nonatomic, assign) NSInteger selectIndex;

+ (instancetype)sharedInstance;

- (NSString*)getBeaconUUID;

- (NSString*)getBeaconItmes;

- (NSString*)getBeaconTitle:(NSInteger)nIndex;

- (NSInteger)totalCount;

@end
