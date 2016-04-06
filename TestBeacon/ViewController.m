//
//  ViewController.m
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "ViewController.h"
#import "SelectLocation.h"
#import "BeaconSourceMgr.h"

@interface ViewController () <UITableViewDelegate, UITableViewDataSource>

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
}

- (NSString*)getTitle:(NSInteger)nIndex {
    
    return [[BeaconSourceMgr sharedInstance] getBeaconTitle:nIndex];
}

- (void)onSelect:(NSInteger)nIndex {
    
    [[BeaconSourceMgr sharedInstance] setSelectIndex:nIndex];
    
    SelectLocation *vctl = [[SelectLocation alloc] init];
    
    [self.navigationController pushViewController:vctl animated:YES];
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"MyCell"];
    
    if (!cell) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"MyCell"];
    }
    
    [cell.textLabel setText:[self getTitle:indexPath.row]];
    
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return [[BeaconSourceMgr sharedInstance] totalCount];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    [self onSelect:indexPath.row];
}


@end
