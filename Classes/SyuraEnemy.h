//
//  SyuraEnemy.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__SyuraEnemy__
#define __SyuraProject__SyuraEnemy__

#include <stdio.h>
#include "cocos2d.h"
#include "Enemy.h"

class SyuraEnemy :public Enemy{
protected:
    SyuraEnemy();
    virtual ~SyuraEnemy();
public:
    
    bool init() override;
    void update(float dt) override;
    CREATE_FUNC(SyuraEnemy);
    /* 修羅キャラに共通する剛体の設定 */
    bool setSyuraBody(cocos2d::PhysicsBody * body);
};




#endif /* defined(__SyuraProject__SyuraEnemy__) */
