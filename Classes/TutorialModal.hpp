//
//  TutorialModal.hpp
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/21.
//
//

#ifndef TutorialModal_hpp
#define TutorialModal_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class TutorialModal : public cocos2d::Layer
{
protected:
//    // コンストラクタ
//    TutorialModal();
//    // デストラクタ
//    virtual ~TutorialModal();
    //音処理クラスのインスタンス作成
    CocosDenshion::SimpleAudioEngine* soundEngineSE = CocosDenshion::SimpleAudioEngine::getInstance();
    
    
public:
   
    virtual bool init();
    //
    void checkIconFlag(char* imageName,Vec2 position);    
    CREATE_FUNC(TutorialModal);
};

#endif /* TutorialModal_hpp */
