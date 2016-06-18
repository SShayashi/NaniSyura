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
#include "NativeBridge.hpp"
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
    
    
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch *oneTouch,Event*event)->bool{
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void TutorialModal::onEnterTransitionDidFinish()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto tutorial = Sprite::create("tutorial.png");
    tutorial->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tutorial->setPosition(winSize / 2);
    this -> addChild(tutorial);
    
    /*ボタンの設置*/
    //閉じるボタンの設定
    auto button = ui::Button::create();
    // タッチイベント True
    button->setTouchEnabled(true);
    // ボタンの中心位置　アーカーポンイント
    button->setAnchorPoint( Vec2::ANCHOR_MIDDLE);
    // 通常状態の画像 押下状態の画像
    button->loadTextures("charadetail/charadetail_close.png","charadetail/charadetail_close_clicked.png", "");
    // ボタンの配置
    button->setPosition(winSize/2 + (tutorial->getContentSize() / 2 ));
    // ボタンのイベント
    button->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            soundEngineSE->playEffect(touch);
            this->removeFromParentAndCleanup(true);
        }
    });
    this->addChild(button,0);
    

    //開始！
    //アニメーションを作成　ScaleTo::create(時間, 比率);
    auto action = ScaleTo::create(0.5, 1);
    tutorial->setScale(1/10);
    
    auto button_action = ScaleTo::create(0.01, 1);
    auto button_delay = DelayTime::create(0.5);
    button->setScale(0.1);
    //アニメーション開始
    tutorial->runAction(action);
    button->runAction(Sequence::create(button_delay,button_action, NULL));

    

    
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