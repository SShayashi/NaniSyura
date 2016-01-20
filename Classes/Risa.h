//
//  Risa.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__Risa__
#define __SyuraProject__Risa__

#include <stdio.h>
#include "SyuraEnemy.h"
class Risa :public SyuraEnemy{
protected:
    Risa();
    virtual ~Risa();
public:
    
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    CREATE_FUNC(Risa);
};

#endif /* defined(__SyuraProject__Risa__) */
