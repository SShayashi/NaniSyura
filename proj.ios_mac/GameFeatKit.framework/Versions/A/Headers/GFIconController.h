//
//  GFIconController.h
//  GameFeatKit
//
//  Created by zaru on 2013/07/08.
//  Copyright (c) 2013年 Basicinc.jp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GFCommon.h"
#import "GFIconView.h"

@interface GFIconController : NSObject {
    int requestType;
    NSTimeInterval refreshTiming;
}
- (void)setRefreshTiming:(int)sec;
- (void)loadAd:(NSString *)site_id;
- (void)stopAd;
- (void)addIconView:(GFIconView *)icon_view;
- (void)setIconTransparentColor:(GFIconView *)icon_view;
- (void)loadAdApi;
- (void)setIconViewData;
- (void)createTimerCheckUUID;
- (void)checkUUID;
- (void)createTimerRefresh;
- (void)invisibleIconAd;
- (void)visibleIconAd;
- (void)removeIconAd;

@property (nonatomic, retain) NSMutableArray *arrIconView;
@property (nonatomic, retain) NSString *uuid;
@property (nonatomic, retain) NSString *gfSiteId;
@property (nonatomic, retain) NSTimer *timer;
@property (nonatomic, retain) NSTimer *refreshTimer;
@property (nonatomic, retain) NSArray *iconAdLists;
@property BOOL isTimerActive;
@property (nonatomic, retain) UIColor *appNameColorHex;

@property (nonatomic, retain) NSURLConnection *httpConnection;
@property (nonatomic, retain) NSMutableData *httpData;
@property (nonatomic, retain) NSString *caller;

@end
