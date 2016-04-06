//
//  SelectLocation.m
//  TestBeacon
//
//  Created by ky on 16/4/6.
//  Copyright © 2016年 ky. All rights reserved.
//

#import "SelectLocation.h"
#import "StoreMgr.h"
#include "YFMyDataProcesser.h"
#include "YFBeaconData.h"
#import "BeaconSourceMgr.h"

@interface SelectLocation() {
    
    YFBeaconDataProcesser *processer;
    
    double m_x;
    
    double m_y;
}

@property (nonatomic, retain) IBOutlet UILabel *ibLabelPos;
@property (nonatomic, retain) NSTimer *timer;
@property (nonatomic, retain) NSTimer *timerSensor;
@property (nonatomic, retain) IBOutlet UIButton *ibStart;
@property (nonatomic, retain) IBOutlet UIButton *ibStop;
@property (nonatomic, retain) IBOutlet UILabel *ibRaw;

@end

@implementation SelectLocation

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    [_ibStart setHidden:NO];
    
    [_ibStop setHidden:YES];
    
    [self setGoBack];
}

- (void)setGoBack {
    
    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    backBtn.frame = CGRectMake(0, 0, 44, 44);
    
    [backBtn setTitle:@"返回" forState:UIControlStateNormal];
    
    [backBtn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
    
    [backBtn addTarget:self action:@selector(doBack:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem *backItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
    
    self.navigationItem.leftBarButtonItem = backItem;
}

- (void)doBack:(id)sender {
    
    [_timer invalidate];
    
    [_timerSensor invalidate];
    
    [self.navigationController popViewControllerAnimated:YES];
}

void loadBeaconData(std::vector<YFBeaconEmitter>& emitters) {
    
    NSString *file = [[BeaconSourceMgr sharedInstance] getBeaconItmes];
    
    NSString *filePath = [[NSBundle mainBundle] pathForResource:file ofType:@"txt"];
    
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
    
    [_ibStart setHidden:YES];
    
    [_ibStop setHidden:NO];
    
    std::vector<YFBeaconEmitter> vctEmitters;
    
    loadBeaconData(vctEmitters);
    
    processer = new MyDataProcesser(vctEmitters);
    
    processer->run();
    
    [_ibLabelPos setText:@"正在接收数据"];
    
    _timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(checkLocation:) userInfo:nil repeats:YES];
}

- (void)stop {
    
    [[StoreMgr sharedInstance] setStopSave:YES];
    
    [_ibStart setHidden:NO];
    
    [_ibStop setHidden:YES];
}

- (IBAction)onStop:(id)sender {
    
    [self stop];
}

- (void)checkLocation:(id)sender {
    
    NSLog(@"checkLocation");
    
    [_timerSensor invalidate];
    
    _timerSensor = nil;
    
    if (processer->CheckAndGetOutput(m_x, m_y)) {
        
        [[StoreMgr sharedInstance] saveRaw:m_x andY:m_y];
        
        [_ibRaw setText:[NSString stringWithFormat:@"%.02f, %.02f", m_x, m_y]];
        
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
