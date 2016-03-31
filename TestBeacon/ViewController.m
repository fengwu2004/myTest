//
//  ViewController.m
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "ViewController.h"
#include "YFMyDataProcesser.h"


@interface ViewController ()

@property (nonatomic, retain) IBOutlet UILabel *ibLabelPos;
@property (nonatomic, retain) NSTimer *timer;

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
}

void loadBeaconData(std::vector<YFBeaconEmitter>& emitters) {
    
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"beacon" ofType:@"txt"];

    NSString *str = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:nil];

    NSArray *array = [str componentsSeparatedByString:@"\n"];

    for (NSInteger i = 0; i < array.count; ++i) {

        NSString *word = array[i];

        NSArray *subWords = [word componentsSeparatedByString:@"\t"];

        if (subWords.count < 3) {

            continue;
        }

        YFBeaconEmitter emitter;
        
        emitter.strId = [subWords[0] UTF8String];
        
        emitter.x = [subWords[1] doubleValue];
        
        emitter.y = [subWords[2] doubleValue];

        emitters.push_back(emitter);
    }
}

- (void)dealloc {
    
    delete processer;
}

- (IBAction)onStart:(id)sender {
    
    std::vector<YFBeaconEmitter> vctEmitters;
    
    loadBeaconData(vctEmitters);
    
    processer = new MyDataProcesser(vctEmitters);
    
    processer->run();
    
    [_ibLabelPos setText:@"无数据"];
    
    _timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(checkLocation:) userInfo:nil repeats:YES];
}

- (void)checkLocation:(id)sender {
    
    double x = 0, y = 0;
    
    if (processer->CheckAndGetOutput(x, y)) {
        
        NSString *location = [NSString stringWithFormat:@"%.02f, %.02f", x, y];
        
        [_ibLabelPos setText:location];
    }
}

@end
