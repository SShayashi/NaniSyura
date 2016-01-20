//
//  Player.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__Player__
#define __SyuraProject__Player__

#include <stdio.h>
#include "cocos2d.h"


class Player :public cocos2d::Sprite
{
protected:
    Player();
    virtual ~Player();
private:
    char fileName[128] = {0};
    cocos2d::Rect rect;
    cocos2d::SpriteFrame *frame;
    
public:
    bool init() override;
    void update(float dt) override;
    void setAnimation();
//    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    CC_SYNTHESIZE(int , _oldSpeed, OldSpeed);
    CC_SYNTHESIZE(int , _speed, Speed);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *> , _frames, Frames);
    CREATE_FUNC(Player);
};


#endif /* defined(__SyuraProject__Player__) */
