//
//  Mobu.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__Mobu__
#define __SyuraProject__Mobu__

#include <stdio.h>
#include "cocos2d.h"
#include "Enemy.h"

class Mobu :public Enemy{
private:
    Mobu();
    virtual ~Mobu();
public:
    
    bool init() override;
    void update(float dt) override;
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    CREATE_FUNC(Mobu);
};



#endif /* defined(__SyuraProject__Mobu__) */
