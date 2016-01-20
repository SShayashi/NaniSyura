//
//  Haruka.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#ifndef __SyuraProject__Haruka__
#define __SyuraProject__Haruka__

#include <stdio.h>
#include "SyuraEnemy.h"
class Haruka :public SyuraEnemy{
protected:
    Haruka();
    virtual ~Haruka();
public:
    
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    CREATE_FUNC(Haruka);
};


#endif /* defined(__SyuraProject__Haruka__) */
