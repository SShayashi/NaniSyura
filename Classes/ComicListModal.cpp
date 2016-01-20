//
//  ComicListModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/15.
//
//

#include "ComicListModal.h"
#include "cocostudio/CocoStudio.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#define touch "sounds/SE/touch.wav"
//横方向に配置されるコミックアイコンの数
const int HORIZONTAL_COUNT = 3;
//縦方向に配置されるコミックアイコンの数
const int VERTICAL_COUNT = 4 ;
// on "init" you need to initialize your instance

ComicListModal::ComicListModal()
: _sqlite(nullptr)
{
    /*Sqliteの初期化処理*/
    _sqlite = UseSqlite::create();
   
}
ComicListModal::~ComicListModal()
{
//      必要なはずだが利用するとmallocエラーを引き起こす
//    CC_SAFE_RELEASE_NULL(_sqlite);
    
}

bool ComicListModal::init()
{
    //初期化
    if ( !CCLayer::init() ) return false;
    
    //画面サイズを取得
    auto winSize = Director::getInstance()->getWinSize();
    
    /* 背景を暗くするレイヤーの設置 */
    auto background = Sprite::create("backpaper.png");
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    background->setPosition(winSize / 2);
    //レイヤーの乗算処理
    BlendFunc blend;
    blend.src = GL_ZERO;
    blend.dst = GL_SRC_COLOR;
    background->setBlendFunc(blend);
    this -> addChild(background);
    
    /*メニューの背景を設置*/
    auto backpaper = Sprite::create("comiclist/backpaper_top.png");
    backpaper->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    backpaper->setPosition(winSize/2);
    this->addChild(backpaper);
    
    
    
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
    button->setPosition(winSize/2 + (backpaper->getContentSize() / 2 ));
    // ボタンのイベント
    button->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
            // 処理
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Close button", 3);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            this->removeFromParentAndCleanup(true);
        }
    });
    this->addChild(button,0);
    
    
    
    
    auto Node = CSLoader::createNode("modal_csd_layer/ComicList.csb");
    Node -> setName("NODE");
    this -> addChild(Node);
    
    /* No01が押された時 */
    auto* No01 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No01"));
    No01->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
    
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No01が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 11);
            sdkbox::PluginGoogleAnalytics::dispatchHits();
            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/haruka_win_kokona.png");
            this->addChild(layer);
            //好きな処理
//            auto layer = CharaDetailModal::create();
//            layer->setName("CharaDetail");
//            this->addChild(layer);
            
        }
    });
    
    
    
    
    /* No02が押された時 */
    auto* No02 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No02"));
    No02->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No02が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 12);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/haruka_win_risa.png");
            this->addChild(layer);

            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No03が押された時 */
    auto* No03 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No03"));
    No03->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No03が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 13);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/kokona_win_miyu.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No04が押された時 */
    auto* No04 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No04"));
    No04->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No04が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 14);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/kokona_win_risa.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No05が押された時 */
    auto* No05 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No05"));
    No05->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No05が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 15);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/miyu_win_haruka.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No06が押された時 */
    auto* No06 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No06"));
    No06->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No06が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 16);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/miyu_win_nene.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No07が押された時 */
    auto* No07 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No07"));
    No07->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No07が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 17);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/nene_win_haruka.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No08が押された時 */
    auto* No08 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No08"));
    No08->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No08が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 18);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/nene_win_kokona.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No09が押された時 */
    auto* No09 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No09"));
    No09->getPosition();
    No09->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No09が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 19);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/risa_win_miyu.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No10が押された時 */
    auto* No10 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No10"));
    No10->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No10が押されました");
            sdkbox::PluginGoogleAnalytics::logEvent("UI", "Button", "Comic view button", 20);
            sdkbox::PluginGoogleAnalytics::dispatchHits();

            soundEngineSE->playEffect(touch);
            auto layer = TopScroll::createWithLayer("comic/risa_win_nene.png");
            this->addChild(layer);
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    
    
    
    
    /*DBを参考に、開放されていない画像はボタンを押せないように、そしてSecretに画像を変更*/


    
    
    /*No1の画像について*/
    if(_sqlite->isOpenImage("comic_icon_haruka_win_kokona.png") != 1){
//        this->addSecretImage(No01->getPosition());
        No01->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_haruka_win_risa.png") != 1){
//        this->addSecretImage(No02->getPosition());
        No02->setEnabled(false);
    }
    
    if(_sqlite->isOpenImage("comic_icon_kokona_win_miyu.png") != 1){
//        this->addSecretImage(No03->getPosition());
        No03->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_kokona_win_risa.png") != 1){
//        this->addSecretImage(No04->getPosition());
        No04->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_miyu_win_haruka.png") != 1){
//        this->addSecretImage(No05->getPosition());
        No05->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_miyu_win_nene.png") != 1){
//        this->addSecretImage(No06->getPosition());
        No06->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_nene_win_haruka.png") != 1){
//        this->addSecretImage(No07->getPosition());
        No07->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_nene_win_kokona.png") != 1){
//        this->addSecretImage(No08->getPosition());
        No08->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_risa_win_miyu.png") != 1){
//        this->addSecretImage(No09->getPosition());
        No09->setEnabled(false);
    }
    if(_sqlite->isOpenImage("comic_icon_risa_win_nene.png") != 1){
//        this->addSecretImage(No10->getPosition());
        No10->setEnabled(false);
    }


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


void ComicListModal::addSecretImage(Vec2 position){
//    auto secret = Sprite::create();
//    secret->initWithFile("comiclist/comic_icon_secret.png");
//    secret->setPosition(position);
//    this->addChild(secret);
}

