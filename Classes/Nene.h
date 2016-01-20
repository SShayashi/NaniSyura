//
//  Nene.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__Nene__
#define __SyuraProject__Nene__

#include <stdio.h>
#include "SyuraEnemy.h"
class Nene :public SyuraEnemy{
protected:
    Nene();
    virtual ~Nene();
public:
    
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    CREATE_FUNC(Nene);
};

#endif /* defined(__SyuraProject__Nene__) */
