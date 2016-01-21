#import <UIKit/UIKit.h>
#import <GameFeatKit/GFView.h>
#import <GameFeatKit/GFController.h>
#import <GameFeatKit/GFIconController.h>
#import <GameFeatKit/GFIconView.h>

@class RootViewController;

// GAMEFEAT MediaID
#define GF_SITE_ID @"10509"
@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@property (nonatomic, retain) GFIconController *gfIconController;
@property (nonatomic, retain) GFIconView *iconView;

//アイコン型GameFeat
- (void)addIconGameFeat;
- (void)showIconGameFeat;
- (void)hideIconGameFeat;

@end

