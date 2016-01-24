//
//  LoseModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/01.
//
//

#include "LoseModal.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "Helper.hpp"
#include "NativeBridge.hpp"

//#include "ui/CocosGUI.h"

using namespace cocos2d;
#define touch "sounds/SE/touch.wav"

bool LoseModal::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("LoseModal");
    sdkbox::PluginGoogleAnalytics::dispatchHits();

    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Node = CSLoader::createNode("modal_csd_layer/LoseLayer.csb");
    Node -> setName("NODE");
    this -> addChild(Node);
    
    /* 女の子リストボタンを押した時の処理 */
    auto* girlListBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("lose_girllist_button"));
    girlListBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Girls list button", 1);
            sdkbox::PluginGoogleAnalytics::dispatchHits();
            soundEngineSE->playEffect(touch);
             CCLOG("女の子リストボタンが押されました");
            //好きな処理
            auto layer = CharaDetailModal::create();
            layer->setName("CharaDetail");
            this->addChild(layer);

        }
    });
    
    /* コミックリストボタンを押した時の処理 */
    auto* comicListBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("lose_comiclist_button"));
    comicListBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            soundEngineSE->playEffect(touch);
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic list button", 2);
            sdkbox::PluginGoogleAnalytics::dispatchHits();
             CCLOG("コミックリストボタンが押されました");
            //好きな処理
            auto layer = ComicListModal::create();
            layer->setName("ComicList");
            this->addChild(layer);

        }
    });
    /* リトライボタンを押した時の処理 */
    auto* retryBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("lose_retry_button"));
    retryBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("リトライボタンが押されました");
            soundEngineSE->playEffect(touch);

            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Retyr button", 0);
            sdkbox::PluginGoogleAnalytics::dispatchHits();
            if(Helper::getInstance()->isGameFeadOpen())
                NativeBridge::showGameFeat();

            
            // 遷移先の画面のインスタンス
                Scene *pScene = GameScene::createScene();
            // 0.5秒かけてフェードアウトしながら次の画面に遷移します
            //    引数１:フィードの時間
            //    引数２：移動先のシーン
            //    引数３：フィードの色（オプション）
                TransitionFade* transition = TransitionFade::create(0.0f, pScene);
            
            // 遷移実行  遷移時のアニメーション
            // 直前のsceneはもう使わないから捨てる、基本はこれになります。
                Director::getInstance()->replaceScene(transition);
            //好きな処理
            this->menuCloseCallback(pSender);
        }
    });
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *oneTouch,Event*event)->bool{
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// menuCloseCallback LoseModalオブジェクトの削除 sender
void LoseModal::menuCloseCallback(Ref* pSender)
{
    // LoseModalオブジェクトの削除
    this->removeFromParentAndCleanup(true);
}
