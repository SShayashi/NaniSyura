//
//  GFWallButtonView.h
//  GameFeatKit
//
//  Created by 狩野恭平 on 2014/03/24.
//  Copyright (c) 2014年 Basicinc.jp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GFController.h"

@interface GFWallButton : UIButton

@property (nonatomic, retain) UIViewController *viewController;
@property (nonatomic, retain) NSString *btn_id;

- (id)init:(UIViewController*)viewCtr;
-(void)setButtonId:(NSString*)btn_id;
@end
