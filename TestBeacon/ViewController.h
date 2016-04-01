//
//  ViewController.h
//  TestBeacon
//
//  Created by ky on 16/3/31.
//  Copyright © 2016年 ky. All rights reserved.
//

#import <UIKit/UIKit.h>

class YFBeaconDataProcesser;

@interface ViewController : UIViewController {
    
    YFBeaconDataProcesser *processer;
    
    double m_x;
    
    double m_y;
}

@end

