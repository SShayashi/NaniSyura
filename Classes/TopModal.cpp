//
//  TopModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/01.
//
//

#include "TopModal.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"

//#include "ui/CocosGUI.h"

USING_NS_CC;

#define touch "sounds/SE/touch.wav"


bool TopModal::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("TopModal");
    sdkbox::PluginGoogleAnalytics::dispatchHits();
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto Node = CSLoader::createNode("modal_csd_layer/TopLayer.csb");
    Node -> setName("NODE");
    this -> addChild(Node);

    /* 女の子リストボタンを押した時の処理 */
    auto* girlListBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("girllist_button"));
    girlListBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            soundEngineSE->playEffect(touch);
            //好きな処理
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Girls list button", 1);
            sdkbox::PluginGoogleAnalytics::dispatchHits();
            CCLOG("女の子リストボタンが押されました");
            auto layer = CharaDetailModal::create();
            layer->setName("CharaDetail");
            this->addChild(layer);
        }
    });
    
    /* コミックリストボタンを押した時の処理 */
    auto* comicListBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("comiclist_button"));
    comicListBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            soundEngineSE->playEffect(touch);
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic list button", 2);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            //好きな処理
            CCLOG("漫画見るリストが押されました");
            auto layer = ComicListModal::create();
            layer->setName("ComicList");
            this->addChild(layer);
        }
    });
    return true;
}

// menuCloseCallback TopModalオブジェクトの削除 sender
void TopModal::menuCloseCallback(Ref* pSender)
{
    // TopModalオブジェクトの削除
    this->removeFromParentAndCleanup(true);
}

