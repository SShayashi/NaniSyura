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
#include "cocos2d.h"
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
    void pushMenu(Ref* pSender);
    void iconHide(Ref* pSender);
    void iconShow(Ref* pSender);
    void onEnterTransitionDidFinish();
    enum {
        tag_gamefeat = 1,
        tag_next
    };
    
public:
   
    virtual bool init();
    
    // タッチ関係のイベント
//    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    CREATE_FUNC(TutorialModal);
};

#endif /* TutorialModal_hpp */
