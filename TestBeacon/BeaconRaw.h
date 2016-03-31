//
//  BeaconRaw.h
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeaconRaw : NSObject

@property (nonatomic, assign) NSInteger time;
@property (nonatomic, copy) NSString *minor;
@property (nonatomic, assign) double x;
@property (nonatomic, assign) double y;
@property (nonatomic, assign) double r;
@property (nonatomic, assign) double M;

@end
