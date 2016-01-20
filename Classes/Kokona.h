//
//  Kokona.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__Kokona__
#define __SyuraProject__Kokona__

#include <stdio.h>
#include "SyuraEnemy.h"
class Kokona :public SyuraEnemy{
protected:
    Kokona();
    virtual ~Kokona();
public:
    
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    CREATE_FUNC(Kokona);
};


#endif /* defined(__SyuraProject__Kokona__) */
