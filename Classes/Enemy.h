//
//  Enemy.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__Enemy__
#define __SyuraProject__Enemy__

#include <stdio.h>
#include "cocos2d.h"

class Enemy :public cocos2d::Sprite
{
protected:
    Enemy();
    virtual ~Enemy();
    char fileName[128] = {0};
    cocos2d::Rect rect;
    cocos2d::SpriteFrame *frame;
    /// アニメーションが何フレームあるか
    const int FRAME_COUNT = 3;

public:
    
    bool init() override;
    void update(float dt) override;
    /* アニメーションの設定 */
    void setAnimation();

    CC_SYNTHESIZE(int , _oldSpeed, OldSpeed);
    CC_SYNTHESIZE(int , _speed, Speed);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *> , _frames, Frames);
    CREATE_FUNC(Enemy);
};



#endif /* defined(__SyuraProject__Enemy__) */
