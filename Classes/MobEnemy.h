//
//  MobEnemy.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__MobEnemy__
#define __SyuraProject__MobEnemy__

#include <stdio.h>
#include "cocos2d.h"
#include "Enemy.h"
#include "Stage.h"

class MobEnemy :public Enemy
{
protected:
    MobEnemy();
    virtual ~MobEnemy();
public:
    
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    /* 敵の移動速度 */
    CREATE_FUNC(MobEnemy);
};


#endif /* defined(__SyuraProject__MobEnemy__) */
