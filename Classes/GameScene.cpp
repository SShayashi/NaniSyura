//
//  GameScene.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TopModal.h"
#include "LoseModal.h"
#include "ClearModal.h"
#include "Haruka.h"
#include "Nene.h"
#include "Kokona.h"
#include "Risa.h"
#include "Miyu.h"
#include <array>
#include "unistd.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

/*  */
int ADD_ENEMY_RATE = 220;
int MAX_SYURAENEMY = 2;

/* 制限時間 */
const float TIME_LIMIT_SECOND = 31;

//サウンド処理
auto soundEngineBGM = SimpleAudioEngine::getInstance();
auto soundEngineSE = SimpleAudioEngine::getInstance();

//効果音
namespace {
    const std::array<std::string, 4> SoundEffects = {
        "sounds/SE/clear.wav", //0
        "sounds/SE/lose.wav", //1
        "sounds/SE/touch.wav", //2
         "sounds/SE/cut.mp3", //3
    };
}

/* コンストラクタ:プレイヤーを初期化 */
GameScene::GameScene()
: _second(TIME_LIMIT_SECOND)
, _state(GameState::READY)
, _stage(nullptr)
, _virPad(nullptr)
, _secondLabel(NULL)

{
    /*Sqliteの初期化処理*/
    _sqlite = UseSqlite::create();
}

GameScene::~GameScene()
{
    //    CC_SAFE_RELEASE_NULL(_stage);なぜかここがエラーになる
    CC_SAFE_RELEASE_NULL(_virPad);
    CC_SAFE_RELEASE_NULL(_secondLabel);
}


Scene* GameScene::createScene()
{
    /* 物理エンジンを有効にしたシーンを作成 */
    auto scene = Scene::createWithPhysics();
    /* 物理空間を取り出す */
    auto world = scene->getPhysicsWorld();
    
    // 重力を設定する
    world->setGravity(Vec2(0, 0));
    
    /* デバッグビルドのとき */
#if COCOS2D_DEBUG > 0
    /* 物理空間にデバッグ用の表示を追加する */
//    world -> setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    
    
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    /* 画面サイズの取得 */
    winSize = Director::getInstance()->getVisibleSize();
    
    /* ステージの読み込み */
    auto stage = Stage::create();
    this -> addChild(stage);
    this -> setStage(stage);
    
    /* バーチャルパッドの実装 */
    auto virPad = VirtualPad::create();
    this->addChild(virPad);
    this->setVirtualPad(virPad);
    
    
    
    /* トップ画面の表示 */
    //////////////////////////////////////
    // レイヤーを追加
    auto layer = TopModal::create();
    layer->setName("TOPMODAL");
    this->addChild(layer);
    
    
    /* マルチタップリスナーの設置 */
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    /* 物体が接触したことを検知するEventListener */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->setEnabled(true);
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_1(GameScene::onContactPresolve, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    /* タイマーラベルの追加 */
    int second = static_cast<int>(_second);
    auto secondLabel = Label::createWithCharMap("time/numbers.png", 43, 52, '0');
    secondLabel = Label::createWithSystemFont(StringUtils::toString(second), "arial", 16);
    this->setSecondLabel(secondLabel);
    
    secondLabel->enableShadow(Color4B::BLACK,Size(0.5,0.5) , 3);
    secondLabel->enableOutline(Color4B::BLACK,1.5);
    secondLabel->setPosition(Vec2(winSize.width /2.0 , winSize.height -70));
    this->addChild(secondLabel);
    
    /* タイマーヘッダーの追加 */
//    auto secondLabelHeader = Label::createWithSystemFont("TIME","MarkerFelt", 30);
//    secondLabelHeader->enableShadow(Color4B::BLACK,Size(0.5,0.5) , 3);
//    secondLabelHeader->enableOutline(Color4B::BLACK,1.5);
//    secondLabelHeader->setPosition(Vec2(winSize.width /2.0 , winSize.height -20));
//    this->addChild(secondLabelHeader);
    
    /* BGMの設定　*/
    soundEngineBGM->setBackgroundMusicVolume(0.5f);
    // soundEngine->preloadBackgroundMusic("sounds/BGM/playbgm.mp3");
    /*bgm開始*/
    soundEngineBGM->playBackgroundMusic("sounds/BGM/playbgm.mp3",true);
    
    /* SEの設定 */
    soundEngineSE->setBackgroundMusicVolume(0.7f);
    for (auto s : SoundEffects) {
        soundEngineSE->preloadEffect(s.c_str());
    }
    
    //    auto rootNode = CSLoader::createNode("GameScene.csb");
    //    addChild(rootNode);
    
    /* update関数（毎フレーム呼び出す関数）の設置 */
    this->scheduleUpdate();
    // １秒ごとに実行される関数の設置
    this->schedule(schedule_selector(GameScene::gameLogic), 1);
    //
    time=0;
    isPauseFlag = false;

    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    // シーン遷移が完了したとき
    Layer::onEnterTransitionDidFinish();
    
    sdkbox::PluginGoogleAnalytics::logScreen("MainScene");
    sdkbox::PluginGoogleAnalytics::dispatchHits();
    
    // 「READY」演出を行う
    this->addReadyLabel();
}

/**
 *タッチ開始
 *@param touches
 *@param event
 */
void GameScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        /* Padの画像範囲 */
        auto padBackRect = _virPad->getPadBack()->getBoundingBox();
        
        /* VirtualPadは、最初は画像の中をタッチしないと反応しない*/
        if(padBackRect.containsPoint(location)){
            /* 準備状態の場合、ゲーム開始フラッグを立てる */
            if(_state == GameState::READY){
                _state = GameState::PLAYING;
                this->onPlaying();
                
            }
            _virPad->startPad((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
            _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        }
        
        
        
        iterator++;
    }
    return;
}

/**
 *タッチ移動
 *@param touches
 *@param event
 */
void GameScene::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /*バーチャルパッド移動中*/
        
        _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        
        iterator++;
    }
    return;
}

/**
 *タッチ終了
 *@param touches
 *@param event
 */
void GameScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /* バーチャルパッドを離す */
        _virPad->endPad(touch->getID());
        
        iterator++;
    }
    return;
}

/**
 * 剛体の接触開始
 *@param contact 接触のインスタンス？
 *
 */
bool GameScene::onContactBegin(PhysicsContact& contact){
    
    /* 衝突した物体２つを取り出す */
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    
    /* 衝突した物体２つのカテゴリを取り出す */
    auto categoryA = bodyA -> getCategoryBitmask();
    auto categoryB = bodyB -> getCategoryBitmask();
    
    /* 衝突した剛体が双方ともMob敵の場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        //        CCLOG("Mob敵とMob敵がぶつかりました");
        
        return true;
    }
    
    /* MOB敵が衝突したとき、片方が敵でない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        
        /* 修羅場に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            //
            //            /* 修羅場エリアリストに挿入 */
            //            auto syuraba = _stage->getSyuraarea();
            //            syuraba.pushBack(bodyA->getNode());
            //            _stage->setSyuraarea(syuraba);
            //
            //            //            CCLOG("%zd", _stage->getSyuraarea().size());
            //            //            _stage->getSyuraarea().insert(_stage->getSyuraarea().size(), bodyB->getNode());
            //            CCLOG("敵「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            //            CCLOG("敵「壁なう」");
            return true;
        }
        /* 神５に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
            //            CCLOG("敵「神5なう」");
            return true;
        }
        
        
    }else if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        /*修羅場に接触した場合*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場リストにオブジェクトを追加 */
            //            /* 修羅場エリアリストに挿入 */
            //            auto syuraba = _stage->getSyuraarea();
            //            syuraba.pushBack(bodyB->getNode());
            //            _stage->setSyuraarea(syuraba);
            //            //            CCLOG("%zd", _stage->getSyuraarea().size());
            //            CCLOG("敵「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
            //            CCLOG("敵「壁なう」");
            return true;
        }
        /* 神５に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
            //            CCLOG("敵「神5なう」");
            return true;
        }
        
    }
    
    /* 衝突した剛体が双方とも修羅キャラの場合 */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        //        CCLOG("修羅キャラと修羅キャラががぶつかりました");
        return true;
    }
    
    /* 修羅キャラが衝突したとき、片方が修羅キャラでない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        
        /* 修羅場に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアリストに挿入 */
            auto syuraba = _stage->getSyuraarea();
            syuraba.pushBack(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            CCLOG("神５「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            CCLOG("神5「壁なう」");
            return true;
        }
        /* Mob敵に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
            CCLOG("神５「モブ敵とぶつかりました」");
            return true;
        }
        
        
    }else if(categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        /*修羅場に接触した場合*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場リストにオブジェクトを追加 */
            /* 修羅場エリアリストに挿入 */
            auto syuraba = _stage->getSyuraarea();
            syuraba.pushBack(bodyB->getNode());
            _stage->setSyuraarea(syuraba);
            //            CCLOG("%zd", _stage->getSyuraarea().size());
            CCLOG("神5「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
            CCLOG("神5「壁なう」");
            return true;
        }
        /* 神５に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
            CCLOG("敵「神5なう」");
            return true;
        }
        
    }
    
    
    
    
    /* 以下プレイヤーが衝突したときの処理 */
    auto otherShape = contact.getShapeA()->getBody() == _stage->getPlayer()->getPhysicsBody() ? contact.getShapeB() : contact.getShapeA();
    auto body = otherShape->getBody();
    
    auto category = body->getCategoryBitmask();
    //    auto layer = dynamic_cast<TMXLayer *>(body->getNode()->getParent());
    
    if (category & static_cast<int>(Stage::TileType::MOB_ENEMY)+static_cast<int>(Stage::TileType::SYURA_ENEMY)) {
        // ゲームオーバー
        GameScene::onLose();
    } else if (category & (int)Stage::TileType::WALL) {
        //        CCLOG("プレイやー「壁なう」");
    } else if (category & static_cast<int>(Stage::TileType::SYURABA_EREA)) {
        //        CCLOG("プレイヤー「修羅場なう」");
    }
    return true;
}

//同等のキャラがぶつかればお互いに弾かれる
void contactEvenEnemy(PhysicsBody *bodyA , PhysicsBody *bodyB){
    
    auto nowposa = bodyA->getPosition();
    auto nowposb = bodyB->getPosition();
    
    auto delta = nowposa - nowposb;
    auto angle = atan2f(delta.y, delta.x);
    
    //        auto angle = Vec2::angle(bodyA->getPosition(),bodyB->getPosition());
    /* 角度を算出 */
    /* 動作量 */
    float MoveX =  cosf(angle);
    float MoveY =  sinf(angle);
    auto moveA = MoveBy::create(0.3, Vec2(MoveX,MoveY)*100);
    auto moveB = MoveBy::create(0.3, -Vec2(MoveX,MoveY)*100);
    
    bodyA->getNode()->runAction(moveA);
    bodyB->getNode()->runAction(moveB);

}

//修羅キャラとMobがぶつかった時の処理、Mobだけ弾き飛ばされる
void contactSyuraAndMob(PhysicsBody *Syura , PhysicsBody *Mob){
    auto nowposa = Syura->getPosition();
    auto nowposb = Mob->getPosition();
    
    auto delta = nowposa - nowposb;
    auto angle = atan2f(delta.y, delta.x);
    
    //        auto angle = Vec2::angle(bodyA->getPosition(),bodyB->getPosition());
    /* 角度を算出 */
    /* 動作量 */
    float MoveX =  cosf(angle);
    float MoveY =  sinf(angle);
    auto moveB = MoveBy::create(0.3, -Vec2(MoveX,MoveY)*100);
    
    Mob->getNode()->runAction(moveB);

    
}





/**
 * 剛体の接触中
 *@param contact 接触クラス？
 *
 */
bool GameScene::onContactPresolve(PhysicsContact& contact){
    
    
    return true;
}

/**
 * 剛体の接触後 ：修羅場に存在する敵の管理を行う
 *@param contact 接触クラス？
 *
 */
void GameScene::onContactSeparate(PhysicsContact& contact){
    /* 修羅場エリアに入っている敵だったら、修羅場エリアのベクターから削除 TODO*/
    
    /* 接触し終わった物体２つを取り出す */
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    
    /* 接触し終わった物体２つのカテゴリを取り出す */
    auto categoryA = bodyA -> getCategoryBitmask();
    auto categoryB = bodyB -> getCategoryBitmask();
    
    /* 接触し終わった剛体が双方とも敵の場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        return ;
    }
    auto syuraba = _stage->getSyuraarea();
    /* 剛体が離れた時、片方がMOB敵でない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        
        /* 修羅場から接触し終わった時 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場エリアリストの中から削除 */
            syuraba.eraseObject(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            
            return ;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            //            CCLOG("敵「壁なう」");
            return ;
        }
    }
    else if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        /*修羅場から接触し終わった時*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場エリアリストの中から削除 */
            syuraba.eraseObject(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            return ;
        }
    }
    
    /* 接触し終わった剛体が双方とも修羅キャラの場合 */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        //        CCLOG("修羅キャラと修羅キャラ離れました");
        return ;
    }
    
    /* 剛体が離れた時、片方が修羅キャラではない */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアヴェクターから削除 */
            syuraba.eraseObject(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            
            return ;
        }
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            return ;
        }
        if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
            return ;
        }
        
    }else if(categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアヴェクターから削除 */
            syuraba.eraseObject(bodyB->getNode());
            _stage->setSyuraarea(syuraba);
            
            return ;
        }
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
            return ;
        }
        if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
            return ;
        }
    }
    return;
}

/**ゲーム中の準備状態の処理
 *
 *
 */
void GameScene::onReady(){
    CCLOG("GameOnReady");
}



/** ゲームオーバー処理
 *
 *
 */
void GameScene::onLose(){

    CCLOG("GameOver!!!");
    sdkbox::PluginGoogleAnalytics::logEvent("System", "Event", "Game Over", 5);
    sdkbox::PluginGoogleAnalytics::dispatchHits();

    //bgm停止
    soundEngineBGM->stopBackgroundMusic();
    
   
    

    // レイヤーを追加
    auto layer = LoseModal::create();
    layer->setName("LoseModal");
    this->addChild(layer);
    /* 動きを止める処理 */
    this->swichPauseFlag();
    
    
    //0.5秒待ちからのルーズ音
    usleep(500000);
    soundEngineSE->playEffect(SoundEffects[1].c_str());
}
/** ゲームクリア処理
 *
 *
 */
void GameScene::onClear(){
    CCLOG("gameClear!!");
    sdkbox::PluginGoogleAnalytics::logEvent("System", "Event", "Game Clear", 6);
    sdkbox::PluginGoogleAnalytics::dispatchHits();

    //bgm停止
    soundEngineBGM->stopBackgroundMusic();

        // レイヤーを追加
    auto layer = ClearModal::create();
    layer->setName("ClearModal");
    this->addChild(layer);
    /* もし修羅場を起こしていたらここに処理を追加 */
    
    /* 修羅場ボタンを追加して新しい修羅場が見れる。なお、発生させる修羅場が3になるとエラーが出る 　要編集TODO*/
    if(_syuraIcon.size() > 1){
        auto menu = Menu::create(_syuraIcon.at(0),_syuraIcon.at(1), NULL);
        menu->alignItemsHorizontallyWithPadding(15);
        menu->setPosition(Vec2(320,450));
        layer->addChild(menu);
        _sqlite->openImage(_syuraIconName.at(0));
        _sqlite->openImage(_syuraIconName.at(1));
        
        
    }else if(_syuraIcon.size() > 0){
        auto menu = Menu::create(_syuraIcon.at(0), NULL);
        menu->alignItemsHorizontallyWithPadding(15);
        menu->setPosition(Vec2(320,450));
        layer->addChild(menu);
        _sqlite->openImage(_syuraIconName.at(0));
    }else{
        
    }
    
    //0.2秒待ちからのクリア音
    usleep(200000);
    soundEngineSE->playEffect(SoundEffects[0].c_str());
    
    /* 押せば漫画を見れるようにする！ */
    /* 動きを止める処理 */
    this->swichPauseFlag();
    
}

/** 修羅場中の処理
 *
 */
void GameScene::onSyuraba(){
    
    sdkbox::PluginGoogleAnalytics::logEvent("System", "Event", "Generate Syuraba", 9);
    sdkbox::PluginGoogleAnalytics::dispatchHits();

    
    /* ゲームを中断する */
    this->swichPauseFlag();
    //BGM一時停止　cutSE開始
    soundEngineBGM->pauseBackgroundMusic();
    auto cutID = soundEngineSE->playEffect(SoundEffects[3].c_str());
    /* 背景を暗くするレイヤーを作って貼る */
    auto syuraLayer = Layer::create();
    //    auto backPaper = Sprite::create("backpaper.png");
    //    backPaper->setPosition(Vec2(0,winSize.height));
    //    syuraLayer->addChild(backPaper);
    this->addChild(syuraLayer);
    //背景を暗くする画像の貼り付け
    auto backpaper = Sprite::create("backpaper.png");
    backpaper->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    backpaper->setPosition(winSize / 2);
    //レイヤーの乗算処理
    BlendFunc blend;
    blend.src = GL_ZERO;
    blend.dst = GL_SRC_COLOR;
    backpaper->setBlendFunc(blend);
    syuraLayer -> addChild(backpaper);
    
    /* ここでどのカットインをいれるか判定 */
    auto filename = this->getCutInFileName((SyuraEnemy*)_stage->getSyuraarea().at(0), (SyuraEnemy*)_stage->getSyuraarea().at(1));
    /* カットインのファイル名から最後に表示させるアイコンを判別 */
    _syuraIcon.pushBack(getIconButton(filename));
    /* カットインのファイル名から最後に表示させるアイコンの画像名を入力 */
    _syuraIconName.push_back(getIconNameFromCutImage(filename));
    
    std::string path = "comiclist/";
    /* 修羅場アイコンを右上に表示させる */
    auto icon = Sprite::create(path.append(_syuraIconName.back()));
    icon->setScale(0.5, 0.5);
    icon->setPosition(Vec2(winSize.width /1.2 , winSize.height -80*_syuraIconName.size()));
    this->addChild(icon);

//    icon->setPosition(900,900+30*_syuraIconName.size());
//    _stage->addChild(icon);
    
    
    /* カットを入れるアニメーション */
    auto cut = Sprite::create(filename);
    cut->setPosition(Vec2(winSize.width,winSize.height/2));
    syuraLayer->addChild(cut);
    auto move = MoveTo::create(1, Vec2(winSize.width/2, winSize.height/2));
    /* 中央で一時停止 */
    auto stop = MoveTo::create(1, Vec2(winSize.width/2, winSize.height/2));
    auto sequence = Sequence::create(move,stop, NULL);
    cut ->runAction(sequence);
    /* レイヤーを乗算にしてかぶせる処理TODO */
    this->runAction(Sequence::create(DelayTime::create(2),CallFunc::create([=](){
        /* 2秒後に処理を実行 */
        syuraLayer->removeFromParent();
        //BGM再開　cutSE中止
        soundEngineBGM->resumeBackgroundMusic();
        
        soundEngineSE->stopEffect(cutID);
        /* アニメーションが終わったらゲームを再度開始 */
        this->swichPauseFlag();
        
        
    }),nullptr));
    /* レイヤーを消す */
    
}

/**ゲーム中へ移行する時、１度だけ呼ぶ処理
 * タイトルからパッド触ったときと
 *　Pauseから戻ってきた時
 */
void GameScene::onPlaying(){
    CCLOG("GameOnPlaying");
    
    sdkbox::PluginGoogleAnalytics::logEvent("System", "Event", "on plyaing", 6);
    sdkbox::PluginGoogleAnalytics::dispatchHits();

    /* TopModal画面を消す */
    TopModal * topModal = this->getChildByName<TopModal *>("TOPMODAL");
    topModal->menuCloseCallback(this);
    //    TopModal::menuCloseCallback(cocos2d::Ref *pSender);
    this->swichPauseFlag();

    
    
}
/** ゲーム開始時の処理
 *
 *
 */
void GameScene::addReadyLabel()
{
    //時間を止める！
    swichPauseFlag();


    //    cocos2d::Director::getInstance()->pause();
}



void GameScene::update(float dt){
    /* プレイヤーにスピードをセット */
    _stage->getPlayer()->setSpeed(_virPad->getSpeed());
    /* バーチャルパッドの操作 */
    if( _virPad->isTouch()){
        
        /*　バーチャルパッドの移動量でプレイヤーを操作 */
        /*　現在の位置を取得　*/
        Vec2 nowPosition = _stage->getPlayer()->getPosition();
        /* パッドから読み込んだ移動量を取得 */
        Vec2 padMovement = Vec2(_virPad->getCosX()*_virPad->getSpeed(), _virPad->getSinY()*_virPad->getSpeed());
        /* プレイヤーwo新しい位置に設定 */
        Vec2 newPosition = nowPosition + padMovement;
        /* プレイヤーの位置を更新 */
        //座標で更新
        _stage->getPlayer()->setPosition(newPosition);
        //物理エンジンでキャラの位置を移動(本当は物理エンジンで実現するのが好ましいが現在は簡単のため座標で移動)
        //        _stage->getPlayer()->getPhysicsBody()->setVelocity(padMovement);
        
        /*プレイヤーが画面外に飛び出さないように設定*/
        auto position = _stage->getPlayer()->getPosition().getClampPoint(Vec2(0,0), _stage->getTiledMap()->getContentSize());
        _stage->getPlayer()->setPosition(position);
        //    CCLOG("%d\n",_virPad->getSpeed());
    }
    
    /* プレイ中になったら時間を減らし出し、また、修羅場の判定をとる */
    if(_state == GameState::PLAYING){
        /* 修羅場エリアに入った時の処理 */
        if( _stage->getSyuraarea().size() >= 2){
            CCLOG("修羅場発生！！！");
            this->onSyuraba();
            auto syuraba = _stage->getSyuraarea();
            
            auto winEnemy = battleSyuraEnemy((SyuraEnemy*)syuraba.at(0), (SyuraEnemy*)syuraba.at(1));
            
            /* ここが大丈夫か見るTODO */
            
            
            for (const auto& enemy : syuraba)
            {
                if(enemy != (Node*)winEnemy ){
                    enemy->removeFromParent();
                    syuraba.eraseObject(enemy);
                }
                
            }
            
            
            //            auto itr = syuraba.begin();
            //            while (itr != syuraba.end())
            //            {
            //                if((*itr) != (Node*)winEnemy){
            //                    (*itr)->removeFromParent();
            //                    itr = syuraba.erase(itr);
            //
            //                }
            //            }
            /* ベクターの中からも全てのオブジェクトを削除 */
            //            syuraba.clear();
            _stage->setSyuraarea(syuraba);
        }
        
        /* 残り時間を減らす */
        _second -= dt;
        /* 表示の更新 */
        int second = static_cast<int>(_second);
        _secondLabel->setString(StringUtils::toString(second));
        
        int random = rand() % ADD_ENEMY_RATE;
        if( random == 0){
            _stage->addEnemyOnStage();
        }
        _stage->moveEnemys();
        /* 時間が0になったら */
        if(_second < 0 ){
            _state = GameState::CLEAR;
            this->onClear();
        }
    }
    
}
/**１秒間に一回呼び出される関数
 *
 *
 */
void GameScene::gameLogic(float dt){
    /* 6秒に一回実行 */
    if(int(TIME_LIMIT_SECOND - _second) % 7 == 6){
        _stage->addSyuraEnemyOnStage();
        CCLOG("add Syura enemy");
    }
}

/** ゲームのポーズスイッチを切り替える
 * 剛体やステージ場の敵、パッド操作等を諸々止める処理をまとめただけ
 *
 */
void GameScene::swichPauseFlag()
{
    /* フラグを反転させる */
    isPauseFlag = !isPauseFlag;
    
    if(isPauseFlag){
        /* GameSceneのupdateを切る */
        this->unscheduleUpdate();
        this->unschedule(schedule_selector(GameScene::gameLogic));
        /* stageも止める */
        _stage->unscheduleUpdate();
        /* パッド */
        /* プレイヤーのスピードを0にする */
        _stage->getPlayer()->setSpeed(0);
        for (const auto& enemy : _stage->getEnemys())
        {
            enemy->pauseSchedulerAndActions();
        }
        //        /* プレイヤーの物理演算を切る */
        //        _stage->getPlayer()->getPhysicsBody()->setEnable(false);
        //
        //        /* 敵の物理演算を切る */
        //        for (const auto& enemy : _stage->getEnemys())
        //        {
        //            auto enemyTag = enemy-> getTag();
        //
        //            /* Mobキャラの場合 */
        //            if(enemyTag == (int)Stage::TileType::MOB_ENEMY){
        //                auto mobenemy = (MobEnemy*) enemy;
        //                mobenemy->getPhysicsBody()->setEnable(false);
        //            }
        //            /* 修羅キャラの場合 */
        //            if(enemyTag == (int)Stage::TileType::SYURA_ENEMY){
        //                auto syuraenemy = (SyuraEnemy*) enemy;
        //                syuraenemy->getPhysicsBody()->setEnable(false);
        //            }
        //        }
    }else{
        /* 止まっていた処理を動かす */
        this->scheduleUpdate();
        this->schedule(schedule_selector(GameScene::gameLogic), 1);
        _stage->scheduleUpdate();
        _stage->getPlayer()->getPhysicsBody()->setEnabled(true);
        
        for (const auto& enemy : _stage->getEnemys())
        {
            enemy->resumeSchedulerAndActions();
        }
        
        /* 敵の物理演算を入れる */
        //        for (const auto& enemy : _stage->getEnemys())
        //        {
        //            auto enemyTag = enemy-> getTag();
        //            /* Mobキャラの場合 */
        //            if(enemyTag == (int)Stage::TileType::MOB_ENEMY){
        //                auto mobenemy = (MobEnemy*) enemy;
        //                mobenemy->getPhysicsBody()->setEnable(true);
        //            }
        //            /* 修羅キャラの場合 */
        //            if(enemyTag == (int)Stage::TileType::SYURA_ENEMY){
        //                auto syuraenemy = (SyuraEnemy*) enemy;
        //                syuraenemy->getPhysicsBody()->setEnable(true);
        //            }
        //        }
    }
}

/** 渡した修羅キャラで買った方のみを返す関数
 *@param syuraEnemyA 修羅キャラの片方
 *@param syuraEnemyB 修羅キャラの片方
 *@return 勝った方の修羅キャラ
 */
SyuraEnemy *GameScene::battleSyuraEnemy(SyuraEnemy *syuraEnemyA,SyuraEnemy *syuraEnemyB){
    
    CCLOG("%s",typeid(*syuraEnemyA).name());
    CCLOG("%s",typeid(*syuraEnemyB).name());
    
    GameScene::SyuraEnemys enemyA,enemyB;
    
    /* クラスを見て共用隊の値を入れていく*/
    if(strstr(typeid(*syuraEnemyA).name(), "Haruka") != NULL){
        enemyA = SyuraEnemys::Haruka;
        //        Haruka* syuraEnemyA = dynamic_cast<Haruka*>(syuraEnemyA);
        
    }else if(strstr(typeid(*syuraEnemyA).name(), "Nene") != NULL){
        enemyA = SyuraEnemys::Nene;
        //        Nene* syuraEnemyA = dynamic_cast<Nene*>(syuraEnemyA);
        
    }else if (strstr(typeid(*syuraEnemyA).name(), "Risa") != NULL){
        enemyA = SyuraEnemys::Risa;
        //        Risa* syuraEnemyA = dynamic_cast<Risa*>(syuraEnemyA);
        
    }else if (strstr(typeid(*syuraEnemyA).name(), "Miyu") != NULL){
        enemyA = SyuraEnemys::Miyu;
        //        Miyu* syuraEnemyA = dynamic_cast<Miyu*>(syuraEnemyA);
        
    }else if (strstr(typeid(*syuraEnemyA).name(), "Kokona") != NULL){
        enemyA = SyuraEnemys::Kokona;
        //        Kokona* syuraEnemyA = dynamic_cast<Kokona*>(syuraEnemyA);
        
    }else{
        CCLOG("ここにくることはないはず");
        return nullptr;
    }
    
    
    if(strstr(typeid(*syuraEnemyB).name(), "Haruka") != NULL){
        enemyB = SyuraEnemys::Haruka;
        //        Haruka* syuraEnemyB = dynamic_cast<Haruka*>(syuraEnemyB);
        
    }else if(strstr(typeid(*syuraEnemyB).name(), "Nene") != NULL){
        enemyB = SyuraEnemys::Nene;
        //        Nene* syuraEnemyB = dynamic_cast<Nene*>(syuraEnemyB);
        
    }else if (strstr(typeid(*syuraEnemyB).name(), "Risa") != NULL){
        enemyB = SyuraEnemys::Risa;
        //        Risa* syuraEnemyB = dynamic_cast<Risa*>(syuraEnemyB);
        
    }else if (strstr(typeid(*syuraEnemyB).name(), "Miyu") != NULL){
        enemyB = SyuraEnemys::Miyu;
        //        Miyu* syuraEnemyB = dynamic_cast<Miyu*>(syuraEnemyB);
        
    }else if (strstr(typeid(*syuraEnemyB).name(), "Kokona") != NULL){
        enemyB = SyuraEnemys::Kokona;
        //        Kokona* syuraEnemyB = dynamic_cast<Kokona*>(syuraEnemyB);
        
    }else{
        CCLOG("ここにくることはないはず");
        return nullptr;
    }
    
    
    /* 変数に入った値からどちらが勝つか判定する */
    switch (enemyA) {
            /* はるかは　りさ　ここな　に勝利 */
        case SyuraEnemys::Haruka :
            
            if(enemyB == SyuraEnemys::Nene){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Risa){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Miyu){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Kokona){
                return syuraEnemyA;
            }
            
            break;
            /* ねねは、ここな　はるか　に勝利 */
        case SyuraEnemys::Nene   :
            
            if(enemyB == SyuraEnemys::Haruka){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Risa){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Miyu){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Kokona){
                return syuraEnemyA;
            }
            
            break;
            /* りさは、みゆ　ねね　に勝利 */
        case SyuraEnemys::Risa   :
            if(enemyB == SyuraEnemys::Haruka){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Nene){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Miyu){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Kokona){
                return syuraEnemyB;
            }
            
            break;
            /* みゆは、　はるか　ねね　に勝利 */
        case SyuraEnemys::Miyu   :
            if(enemyB == SyuraEnemys::Haruka){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Nene){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Risa){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Kokona){
                return  syuraEnemyB;
            }
            
            break;
            /* ここなは、　りさ　みゆに勝利 */
        case SyuraEnemys::Kokona :
            
            if(enemyB == SyuraEnemys::Haruka){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Nene){
                return syuraEnemyB;
            }
            if(enemyB == SyuraEnemys::Risa){
                return syuraEnemyA;
            }
            if(enemyB == SyuraEnemys::Miyu){
                return syuraEnemyA;
            }
            
            break;
            
        default:
            CCLOG("ここに来ることは無いはず");
            return nullptr;
            break;
    }
    
    return nullptr;
}


/** 渡した修羅キャラで買った方のみを返す関数
 *@param syuraEnemyA 修羅キャラの片方
 *@param syuraEnemyB 修羅キャラの片方
 *@return それらに適したカットインのファイル名
 */
char *GameScene::getCutInFileName(SyuraEnemy *syuraEnemyA,SyuraEnemy *syuraEnemyB){
    
    CCLOG("%s",typeid(*syuraEnemyA).name());
    CCLOG("%s",typeid(*syuraEnemyB).name());
    
    GameScene::SyuraEnemys enemyA,enemyB;
    
    /* クラスを見て共用隊の値を入れていく*/
    if(strstr(typeid(*syuraEnemyA).name(), "Haruka") != NULL){
        enemyA = SyuraEnemys::Haruka;
        //        Haruka* syuraEnemyA = dynamic_cast<Haruka*>(syuraEnemyA);
        
    }else if(strstr(typeid(*syuraEnemyA).name(), "Nene") != NULL){
        enemyA = SyuraEnemys::Nene;
        //        Nene* syuraEnemyA = dynamic_cast<Nene*>(syuraEnemyA);
        
    }else if (strstr(typeid(*syuraEnemyA).name(), "Risa") != NULL){
        enemyA = SyuraEnemys::Risa;
        //        Risa* syuraEnemyA = dynamic_cast<Risa*>(syuraEnemyA);
        
    }else if (strstr(typeid(*syuraEnemyA).name(), "Miyu") != NULL){
        enemyA = SyuraEnemys::Miyu;
        //        Miyu* syuraEnemyA = dynamic_cast<Miyu*>(syuraEnemyA);
        
    }else if (strstr(typeid(*syuraEnemyA).name(), "Kokona") != NULL){
        enemyA = SyuraEnemys::Kokona;
        //        Kokona* syuraEnemyA = dynamic_cast<Kokona*>(syuraEnemyA);
        
    }else{
        CCLOG("ここにくることはないはず");
        return nullptr;
    }
    
    
    if(strstr(typeid(*syuraEnemyB).name(), "Haruka") != NULL){
        enemyB = SyuraEnemys::Haruka;
        //        Haruka* syuraEnemyB = dynamic_cast<Haruka*>(syuraEnemyB);
        
    }else if(strstr(typeid(*syuraEnemyB).name(), "Nene") != NULL){
        enemyB = SyuraEnemys::Nene;
        //        Nene* syuraEnemyB = dynamic_cast<Nene*>(syuraEnemyB);
        
    }else if (strstr(typeid(*syuraEnemyB).name(), "Risa") != NULL){
        enemyB = SyuraEnemys::Risa;
        //        Risa* syuraEnemyB = dynamic_cast<Risa*>(syuraEnemyB);
        
    }else if (strstr(typeid(*syuraEnemyB).name(), "Miyu") != NULL){
        enemyB = SyuraEnemys::Miyu;
        //        Miyu* syuraEnemyB = dynamic_cast<Miyu*>(syuraEnemyB);
        
    }else if (strstr(typeid(*syuraEnemyB).name(), "Kokona") != NULL){
        enemyB = SyuraEnemys::Kokona;
        //        Kokona* syuraEnemyB = dynamic_cast<Kokona*>(syuraEnemyB);
        
    }else{
        CCLOG("ここにくることはないはず");
        return nullptr;
    }
    
    
    /* 変数に入った値からどちらが勝つか判定する */
    switch (enemyA) {
            /* はるかは　りさ　ここな　に勝利 */
        case SyuraEnemys::Haruka :
            
            if(enemyB == SyuraEnemys::Nene){
                return "cut/nene_haruka.png";
            }
            if(enemyB == SyuraEnemys::Risa){
                return "cut/haruka_risa.png";
            }
            if(enemyB == SyuraEnemys::Miyu){
                return "cut/miyu_haruka.png";
            }
            if(enemyB == SyuraEnemys::Kokona){
                return "cut/haruka_kokona.png";
            }
            
            break;
            /* ねねは、ここな　はるか　に勝利 */
        case SyuraEnemys::Nene   :
            
            if(enemyB == SyuraEnemys::Haruka){
                return "cut/nene_haruka.png";
            }
            if(enemyB == SyuraEnemys::Risa){
                return "cut/risa_nene.png";
            }
            if(enemyB == SyuraEnemys::Miyu){
                return "cut/miyu_nene.png";
            }
            if(enemyB == SyuraEnemys::Kokona){
                return "cut/nene_kokona.png";
            }
            
            break;
            /* りさは、みゆ　ねね　に勝利 */
        case SyuraEnemys::Risa   :
            if(enemyB == SyuraEnemys::Haruka){
                return "cut/haruka_risa.png";
            }
            if(enemyB == SyuraEnemys::Nene){
                return "cut/risa_nene.png";
            }
            if(enemyB == SyuraEnemys::Miyu){
                return "cut/risa_miyu.png";
            }
            if(enemyB == SyuraEnemys::Kokona){
                return "cut/kokona_risa.png";
            }
            
            break;
            /* みゆは、　はるか　ねね　に勝利 */
        case SyuraEnemys::Miyu   :
            if(enemyB == SyuraEnemys::Haruka){
                return "cut/miyu_haruka.png";
            }
            if(enemyB == SyuraEnemys::Nene){
                return "cut/miyu_nene.png";
            }
            if(enemyB == SyuraEnemys::Risa){
                return "cut/risa_miyu.png";
            }
            if(enemyB == SyuraEnemys::Kokona){
                return  "cut/miyu_kokona.png";
            }
            
            break;
            /* ここなは、　りさ　みゆに勝利 */
        case SyuraEnemys::Kokona :
            
            if(enemyB == SyuraEnemys::Haruka){
                return "cut/haruka_kokona.png";
            }
            if(enemyB == SyuraEnemys::Nene){
                return "cut/nene_kokona.png";
            }
            if(enemyB == SyuraEnemys::Risa){
                return "cut/kokona_risa.png";
            }
            if(enemyB == SyuraEnemys::Miyu){
                return "cut/kokona_miyu.png";
            }
            
            break;
            
        default:
            CCLOG("ここに来ることは無いはず");
            return nullptr;
            break;
    }
    
    return nullptr;
}

//カットのファイル名から漫画アイコンのボタンを返す
MenuItemImage *GameScene::getIconButton(char *cutfilename){
    //はるかVSここなの場合
    if(strstr(cutfilename, "haruka_kokona.png")){
        auto harukaWinKokona = MenuItemImage::create("comiclist/comic_icon_haruka_win_kokona.png","",
                                                     [this](Ref* ref){
                                                         soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                         auto layer = TopScroll::createWithLayer("comic/haruka_win_kokona.png");
                                                         this->addChild(layer);
                                                         
                                                     });
        return harukaWinKokona;
    }
    
    //ここなVSみゆの場合
    if(strstr(cutfilename, "kokona_miyu.png")){
        auto miyuWinHaruka = MenuItemImage::create("comiclist/comic_icon_kokona_win_miyu.png","",
                                                   [this](Ref* ref){
                                                       soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                       auto layer = TopScroll::createWithLayer("comic/miyu_win_haruka.png");
                                                       this->addChild(layer);

                                                   });
        return miyuWinHaruka;
        
    }
    
    //はるかVSりさの場合
    if(strstr(cutfilename, "haruka_risa.png")){
        auto harukaWinRisa = MenuItemImage::create("comiclist/comic_icon_haruka_win_risa.png","",
                                                   [this](Ref* ref){
                                                       soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                       auto layer = TopScroll::createWithLayer("comic/haruka_win_risa.png");
                                                       this->addChild(layer);

                                                       
                                                   });
        return harukaWinRisa;
        
    }
    //ここなVSりさの場合
    if(strstr(cutfilename, "kokona_risa.png")){
        auto kokonaWinRisa = MenuItemImage::create("comiclist/comic_icon_kokona_win_risa.png","",
                                                   [this](Ref* ref){
                                                       soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                       auto layer = TopScroll::createWithLayer("comic/kokona_win_risa.png");
                                                       this->addChild(layer);

                                                   });
        return kokonaWinRisa;
        
    }
    //みゆVSはるかの場合
    if(strstr(cutfilename, "miyu_haruka.png")){
        auto miyuWinHaruka = MenuItemImage::create("comiclist/comic_icon_miyu_win_haruka.png","",
                                                   [this](Ref* ref){
                                                       soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                       auto layer = TopScroll::createWithLayer("comic/miyu_win_haruka.png");
                                                       this->addChild(layer);

                                                   });
        return miyuWinHaruka;
        
        
    }
    //みゆVSねねの場合
    if(strstr(cutfilename, "miyu_nene.png")){
        auto miyuWinNene = MenuItemImage::create("comiclist/comic_icon_miyu_win_nene.png","",
                                                 [this](Ref* ref){
                                                     soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                     auto layer = TopScroll::createWithLayer("comic/miyu_win_nene.png");
                                                     this->addChild(layer);

                                                 });
        return miyuWinNene;
        
    }
    //ねねVSはるか
    if(strstr(cutfilename, "nene_haruka.png")){
        auto neneWinHaruka = MenuItemImage::create("comiclist/comic_icon_nene_win_haruka.png","",
                                                   [this](Ref* ref){
                                                       soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                       auto layer = TopScroll::createWithLayer("comic/nene_win_haruka.png");
                                                       this->addChild(layer);

                                                   });
        return neneWinHaruka;
        
    }
    //ねねVSここな
    if(strstr(cutfilename, "nene_kokona.png")){
        auto neneWinKokona = MenuItemImage::create("comiclist/comic_icon_nene_win_kokona.png","",
                                                   [this](Ref* ref){
                                                       soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                       auto layer = TopScroll::createWithLayer("comic/nene_win_kokona.png");
                                                       this->addChild(layer);

                                                   });
        return neneWinKokona;
        
    }
    //りさVSみゆ
    if(strstr(cutfilename, "risa_miyu.png")){
        auto risaWinMiyu = MenuItemImage::create("comiclist/comic_icon_risa_win_miyu.png","",
                                                 [this](Ref* ref){
                                                     soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                     auto layer = TopScroll::createWithLayer("comic/risa_win_miyu.png");
                                                     this->addChild(layer);

                                                 });
        return risaWinMiyu;
        
    }
    //りさVSねね
    if(strstr(cutfilename, "risa_nene.png")){
        auto risaWinNene = MenuItemImage::create("comiclist/comic_icon_risa_win_nene.png","",
                                                 [this](Ref* ref){
                                                     soundEngineSE->playEffect(SoundEffects[2].c_str());
                                                     auto layer = TopScroll::createWithLayer("comic/risa_win_nene.png");
                                                     this->addChild(layer);

                                                 });
        return risaWinNene;
    }
    
    return nullptr;
}
/**カットアイコンのファイル名から、最後に表示させるアイコンのファイル名を取得する
 *
 */
char *GameScene::getIconNameFromCutImage(char* cutfilename){
    
    //はるかVSここなの場合
    if(strstr(cutfilename, "haruka_kokona.png"))
        return "comic_icon_haruka_win_kokona.png";
    //ここなVSみゆの場合
    if(strstr(cutfilename, "kokona_miyu.png"))
       return  "comic_icon_kokona_win_miyu.png";
    //はるかVSりさの場合
    if(strstr(cutfilename, "haruka_risa.png"))
       return "comic_icon_haruka_win_risa.png";
    
    //ここなVSりさの場合
    if(strstr(cutfilename, "kokona_risa.png"))
       return "comic_icon_kokona_win_risa.png";
    
    //みゆVSはるかの場合
    if(strstr(cutfilename, "miyu_haruka.png"))
        return "comic_icon_miyu_win_haruka.png";
    //みゆVSねねの場合
    if(strstr(cutfilename, "miyu_nene.png"))
       return "comic_icon_miyu_win_nene.png";
    //ねねVSはるか
    if(strstr(cutfilename, "nene_haruka.png"))
        return "comic_icon_nene_win_haruka.png";

    //ねねVSここな
    if(strstr(cutfilename, "nene_kokona.png"))
        return "comic_icon_nene_win_kokona.png";
    //りさVSみゆ
    if(strstr(cutfilename, "risa_miyu.png"))
        return "comic_icon_risa_win_miyu.png";

        //リサVSねね
    if(strstr(cutfilename, "risa_nene.png"))
           return  "comic_icon_risa_win_nene.png";

    //ここに来ることはないはず
    return "";
}
