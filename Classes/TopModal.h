//
//  TopModal.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/01.
//
//

#ifndef __SyuraProject__TopModal__
#define __SyuraProject__TopModal__

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/cocosGUI.h"

#include "CharaDetailModal.h"
#include "ComicListModal.h"

#include "SimpleAudioEngine.h"
class TopModal : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    //音処理クラスのインスタンス作成
    CocosDenshion::SimpleAudioEngine* soundEngineSE = CocosDenshion::SimpleAudioEngine::getInstance();

    void menuCloseCallback(Ref* pSender);
    
    void pushMenu01(Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(TopModal);
};


#endif /* defined(__SyuraProject__TopModal__) */
