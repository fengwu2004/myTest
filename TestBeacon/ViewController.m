//
//  ViewController.m
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "ViewController.h"
#include "YFMyDataProcesser.h"
#import "StoreMgr.h"
#include "YFMyDataProcesser.h"

@interface ViewController ()

@property (nonatomic, retain) IBOutlet UILabel *ibLabelPos;
@property (nonatomic, retain) NSTimer *timer;
@property (nonatomic, retain) NSTimer *timerSensor;
@property (nonatomic, retain) IBOutlet UIButton *ibStart;

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
    
    [_ibStart setEnabled:NO];
    
    [_ibStart setTitle:@"已经开始了" forState:UIControlStateDisabled];
    
    std::vector<YFBeaconEmitter> vctEmitters;
    
    loadBeaconData(vctEmitters);
    
    processer = new MyDataProcesser(vctEmitters);
    
    processer->run();
    
    [_ibLabelPos setText:@"无数据"];
    
    _timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(checkLocation:) userInfo:nil repeats:YES];
}

- (void)checkLocation:(id)sender {
    
    [_timerSensor invalidate];
    
    _timerSensor = nil;
    
    if (processer->CheckAndGetOutput(m_x, m_y)) {
        
        _timerSensor = [NSTimer scheduledTimerWithTimeInterval:0.2 target:self selector:@selector(fastNaviProcess:) userInfo:nil repeats:YES];
    }
}

- (void)fastNaviProcess:(id)sender {
    
    processer->OnNaviProcess();
    
    MyDataProcesser *p = (MyDataProcesser *)processer;
    
    location loc = p->Result();
    
    [[StoreMgr sharedInstance] saveLocation:loc.x andY:loc.y];
    
    NSString *location = [NSString stringWithFormat:@"%.02f, %.02f", loc.x, loc.y];
    
    [_ibLabelPos setText:location];
}

@end
