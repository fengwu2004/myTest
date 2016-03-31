//
//  StoreMgr.m
//  Lottery
//
//  Created by user on 16/2/16.
//  Copyright © 2016年 user. All rights reserved.
//

#import "StoreMgr.h"
#import "FMDatabase.h"
#import "Common.h"
#import "BeaconRaw.h"

@interface StoreMgr()

@property (nonatomic, retain) FMDatabase *db;

@end

@implementation StoreMgr

+ (StoreMgr*)sharedInstance {
    
    static StoreMgr *_instance = nil;
    
    static dispatch_once_t predicate;
    
    dispatch_once(&predicate, ^{
        
        _instance = [[StoreMgr alloc] init];
    });
    
    return _instance;
}

- (id)init {
    
    self = [super init];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    NSString *documentDirectory = [paths objectAtIndex:0];
    
    NSString *dbPath = [documentDirectory stringByAppendingPathComponent:@"MyDatabase.db"];
    
    _db = [FMDatabase databaseWithPath:dbPath];
    
    [_db open];
    
    [_db executeUpdate:@"CREATE TABLE Beacon (time integer, minor text, x float, y float, r float, M float)"];
    
    [_db executeUpdate:@"CREATE TABLE Location (x float, y float)"];
    
    [_db class];
    
    return self;
}

- (void)saveBeacon:(NSArray*)beaconRawData {
    
    if (![_db open]) {
        
        return;
    }
    
    for (BeaconRaw *raw in beaconRawData) {
        
        [_db executeUpdate:@"INSERT INTO Beacon (time, minor, x, y, r, M) VALUES (?,?,?,?,?,?)", raw.time, raw.minor, raw.x, raw.y, raw.r, raw.M];
    }
    
    [_db close];
}

- (void)saveLocation:(double)x andY:(double)y {
    
    if (![_db open]) {
        
        return ;
    }
    
    [_db executeUpdate:@"INSERT INTO Location (x, y) VALUES (?,?)", x, y];
    
    [_db close];
}

@end
