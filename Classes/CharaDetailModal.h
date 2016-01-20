//
//  CharaDetailModal.h
//  SyuraProject
//
//  Created by 林 真史 on 2015/08/14.
//
//

#ifndef __SyuraProject__CharaDetailModal__
#define __SyuraProject__CharaDetailModal__

#include <stdio.h>
#include "cocos2d.h"
#include "CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class CharaDetailModal : public cocos2d::Layer
{
    
public:
    const std::vector<std::string> charaImages = {
        "charadetail/detail_futsuo.png",
        "charadetail/detail_mobuko.png",
        "charadetail/detail_haruka.png",
        "charadetail/detail_kokona.png",
        "charadetail/detail_miyu.png",
        "charadetail/detail_nene.png",
        "charadetail/detail_risa.png",
    };
    void menuCloseCallback(Ref* pSender);
    virtual bool init();
    
    CC_SYNTHESIZE_RETAIN(ui::PageView* , _pageView, PageView);
    //音処理クラスのインスタンス作成
    CocosDenshion::SimpleAudioEngine* soundEngineSE = CocosDenshion::SimpleAudioEngine::getInstance();
    
    CREATE_FUNC(CharaDetailModal);
};

#endif /* defined(__SyuraProject__CharaDetailModal__) */
