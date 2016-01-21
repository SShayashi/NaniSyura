//
//  GFController.h
//  GameFeatKit
//
//  Created by n-watanabe on 13/02/25.
//  Copyright (c) 2013年 Basicinc.jp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GFCommon.h"
#import "GFView.h"

@interface GFController : NSObject

+ (void)showGF:(UIViewController *)vc site_id:(NSString *)site_id;
+ (void)showGF:(UIViewController *)vc site_id:(NSString *)site_id btn_id:(NSString*)btn_id;
+ (void)showGF:(UIViewController *)vc site_id:(NSString *)site_id delegate:(id<GFViewDelegate>)delegate;
+ (void)showGF:(UIViewController *)vc site_id:(NSString *)site_id btn_id:(NSString *)btn_id delegate:(id<GFViewDelegate>)delegate;
+ (void)backgroundTask;
+ (void)conversionCheckStop;

+ (void)activateGF:(NSString *)site_id useCustom:(BOOL)useCustom useIcon:(BOOL)useIcon;

+ (BOOL)getGFAds:(id<GFViewDelegate>)del;
+ (void)showGFEntry:(UIViewController *)vc ad:(NSDictionary *)ad;
+ (void)showGFEntry:(UIViewController *)vc ad:(NSDictionary *)ad delegate:(id<GFViewDelegate>)delegate;
+ (void)showGFDL:(UIViewController *)vc ad:(NSDictionary *)ad;

+ (BOOL)openStoreUrl:(NSURLRequest *)request;

@end

