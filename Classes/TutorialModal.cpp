//
//  TutorialModal.cpp
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/21.
//
//

#include "TutorialModal.hpp"
#include "GameScene.h"
//#include "ui/CocosGUI.h"

using namespace cocos2d;
#define touch "sounds/SE/touch.wav"

bool TutorialModal::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //背景を暗くする画像の貼り付け
    auto backpaper = Sprite::create("backpaper.png");
    backpaper->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    backpaper->setPosition(winSize / 2);
    //レイヤーの乗算処理
    BlendFunc blend;
    blend.src = GL_ZERO;
    blend.dst = GL_SRC_COLOR;
    backpaper->setBlendFunc(blend);
    this -> addChild(backpaper);

    auto tutorial = Sprite::create("tutorial.png");
    tutorial->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tutorial->setPosition(winSize / 2);
    tutorial->setScale(1.5, 1.8);
    this -> addChild(tutorial);

    //onTouchEndedだけを使うとバグが出たので、マルチタップにしている
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesEnded = CC_CALLBACK_2(TutorialModal::onTouchesEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

/**
 *タッチ開始
 *@param touches
 *@param event
 */
void TutorialModal::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    soundEngineSE->playEffect(touch);
    this->removeFromParentAndCleanup(true);

    return;
}
