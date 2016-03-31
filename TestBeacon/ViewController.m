//
//  ViewController.m
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "ViewController.h"
#include "YFMyDataProcesser.hpp"


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    std::vector<YFBeaconEmitter> vctEmitters;
    
    processer = new MyDataProcesser(vctEmitters);
    
    processer->run();
}

- (void)dealloc {
    
    delete processer;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
