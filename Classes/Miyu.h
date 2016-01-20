//
//  Miyu.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__Miyu__
#define __SyuraProject__Miyu__

#include <stdio.h>
#include "SyuraEnemy.h"
class Miyu :public SyuraEnemy{
protected:
    Miyu();
    virtual ~Miyu();
public:
    
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    CREATE_FUNC(Miyu);
};


#endif /* defined(__SyuraProject__Miyu__) */
