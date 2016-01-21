//
//  NativeBridge.m
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/22.
//
//

//
//  NativeBridge.m
//  GameFeatSample
//
//  Created by 中村 慎司 on 2013/09/04.
//
//

#import "NativeBridge.hpp"
#include "AppController.h"

#import <GameFeatKit/GFView.h>
#import <GameFeatKit/GFController.h>

/**
 * オファーウォール型GameFeat表示
 */
void NativeBridge::showGameFeat()
{
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [GFController showGF:(UIViewController *)appController.viewController site_id:GF_SITE_ID];
    NSLog(@"showGameFeat");
}

/**
 * アイコン型GameFeat表示
 */
void NativeBridge::showIconGameFeat()
{
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController showIconGameFeat];
    NSLog(@"showIconGameFeat");
}

/**
 * アイコン型GameFeat非表示
 */
void NativeBridge::hideIconGameFeat()
{
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController hideIconGameFeat];
    NSLog(@"hideIconGameFeat");
}