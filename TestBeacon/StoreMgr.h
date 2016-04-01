//
//  StoreMgr.h
//  Lottery
//
//  Created by user on 16/2/16.
//  Copyright © 2016年 user. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface StoreMgr : NSObject

@property (nonatomic, assign) BOOL stopSave;

+ (StoreMgr*)sharedInstance;

- (void)saveBeacon:(NSArray*)beaconRawData;

- (void)saveLocation:(double)x andY:(double)y;

@end
