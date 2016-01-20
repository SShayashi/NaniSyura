//
//  CustomFollow.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/22.
//
//

#ifndef __SyuraProject__CustomFollow__
#define __SyuraProject__CustomFollow__

#include <stdio.h>
#include "cocos2d.h"

enum CustomFollowType{
    kCustomFollowNone,
    kCustomFollowXOnly,
    kCustomFollowYOnly
};

class CustomFollow : public cocos2d::Follow
{
private:
    CustomFollowType _type;
    cocos2d::Rect _marginRect;
    
    CustomFollow();
    ~CustomFollow();
public:
    static CustomFollow* create(cocos2d::Node *followedNode);
    static CustomFollow* create(cocos2d::Node *followedNode, CustomFollowType type);
    static CustomFollow* create(cocos2d::Node *followedNode, cocos2d::Rect marginRect);
    
    virtual void step(float dt) override;
};
#endif /* defined(__SyuraProject__CustomFollow__) */
