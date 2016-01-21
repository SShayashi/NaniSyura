//
//  GFIconView.h
//  GameFeatKit
//
//  Created by zaru on 2013/07/08.
//  Copyright (c) 2013年 Basicinc.jp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "GFCommon.h"

@interface GFIconView : UIView
- (void)setImageUrl:(NSString *)imageUrl;
- (void)setClickUrl:(NSString *)clickUrl;
- (void)setAppName:(NSString *)appName;
- (void)setTouchStatus:(BOOL)flag;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)saveClick:(NSString *)ad_id scheme:(NSString *)scheme click_time:(NSNumber *)click_time;
- (void)setIconData:(NSString *)imageUrl clickUrl:(NSString *)clickUrl appName:(NSString *)appName adId:(NSString *)adId packageName:(NSString *)packageName appNameColor:(UIColor *)appNameColor;
- (int)unixtimestamp;

@property (nonatomic, retain) UIImageView *iconImageView;
@property (nonatomic, retain) UILabel *iconAppName;
@property (nonatomic, retain) NSString *adId;
@property (nonatomic, retain) NSString *packageName;
@property (nonatomic, retain) NSString *url;
@property BOOL fromPopup;
@property (assign) CGRect iconFrame;
@property (assign) CGRect titleFrame;

@end
