//
//  GFWallButtonController.h
//  GameFeatKit
//
//  Created by 狩野恭平 on 2014/03/24.
//  Copyright (c) 2014年 Basicinc.jp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "GFWallButton.h"

@interface GFWallButtonController : NSObject

@property (nonatomic, retain) NSMutableData *httpData;
@property (nonatomic, retain) NSString *wallBtnUrl;
@property (nonatomic, retain) GFWallButton *gfButton;
@property (nonatomic, retain) NSURLConnection *httpConnection;

-(id)init:(GFWallButton*)btnView gfButtonTag:(NSString*)tag;
-(id)init:(GFWallButton*)btnView;
-(void)loadWallButton:(NSString*)tag;
-(void)removeGFButton;

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)http;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;

@end
