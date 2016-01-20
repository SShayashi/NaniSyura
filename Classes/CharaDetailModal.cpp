
//
//  CharaDetailModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/14.
//
//

#include "CharaDetailModal.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#define touch "sounds/SE/touch.wav"
// on "init" you need to initialize your instance
bool CharaDetailModal::init()
{
    //初期化
    if ( !CCLayer::init() ) return false;
    
    //画面サイズを取得
    auto winSize = Director::getInstance()->getWinSize();
    
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
    
    //PageViewを作成これにレイアウトを追加していく
    auto pageView = ui::PageView::create();
    //pageviewのタッチを有効に
    pageView->setTouchEnabled(true);
    pageView->setContentSize(Size(winSize.width,winSize.height));
    pageView->setPosition((winSize - pageView->getContentSize())/2);
    setPageView(pageView);
    this->addChild(_pageView,1);

    
    //pageviewの背景画像
    auto backcard = Sprite::create("charadetail/backcard.png");
    backcard->setPosition(Vec2(pageView->getContentSize().width / 2 , pageView->getContentSize().height/2 - 50));
    this->addChild(backcard,0);
    
    //コンテンツ配置
    for (int i = 0; i < CharaDetailModal::charaImages.size() ; i++) {
        //レイアウトの作成
        auto layout = ui::Layout::create();
        layout->setContentSize(pageView->getContentSize());
        
        //キャラの画像
        auto charaimage = ui::ImageView::create(charaImages.at(i));
        charaimage->setTouchEnabled(true);
        charaimage->setPosition(layout->getContentSize() / 2);
        layout->addChild(charaimage);
        
        /*ボタンの設置*/
        //閉じるボタンの設定
        auto closebutton = ui::Button::create();
        // タッチイベント True
        closebutton->setTouchEnabled(true);
        // ボタンの中心位置　アーカーポンイント
        closebutton->setAnchorPoint( Vec2::ANCHOR_MIDDLE);
        // 通常状態の画像 押下状態の画像
        closebutton->loadTextures("charadetail/charadetail_close.png","charadetail/charadetail_close_clicked.png", "");
        // ボタンの配置
        closebutton->setPosition(winSize/2 + (charaimage->getContentSize() / 2 ));
        // ボタンのイベント
        closebutton->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
                sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Close button", 3);
                sdkbox::PluginGoogleAnalytics::dispatchHits();

                // 処理
                soundEngineSE->playEffect(touch);
                this->removeFromParentAndCleanup(true);
            }
        });
        layout->addChild(closebutton,0);
        
        
//        //矢印画像
//        if(i != CharaDetailModal::charaImages.size() - 1 ){
//            auto rightbutton = ui::ImageView::create("charadetail/right_button.png");
//            rightbutton->setPosition(Vec2(layout->getContentSize().width * 5/6,layout->getContentSize().height / 2));
//            layout->addChild(rightbutton,1);
//        }
//
//        
//        if(i != 0){
//            auto leftbutton = ui::ImageView::create("charadetail/left_button.png");
//            leftbutton->setPosition(Vec2(layout->getContentSize().width * 1/6,layout->getContentSize().height / 2));
//            layout->addChild(leftbutton,2);
//
//        
        pageView->insertPage(layout, i);
    }
    
    
    return true;
    
}

// menuCloseCallback オブジェクトの削除 sender
void CharaDetailModal::menuCloseCallback(Ref* pSender)
{
    // ClearModalオブジェクトの削除
    this->removeFromParentAndCleanup(true);
}