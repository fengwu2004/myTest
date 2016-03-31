//
//  BeaconRaw.h
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeaconRaw : NSObject

@property (nonatomic, retain) NSNumber *time;
@property (nonatomic, copy) NSString *minor;
@property (nonatomic, retain) NSNumber *x;
@property (nonatomic, retain) NSNumber *y;
@property (nonatomic, retain) NSNumber *r;
@property (nonatomic, retain) NSNumber *M;

@end
