//
//  Player.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Player.h"
#include "Stage.h"

USING_NS_CC;
int FRAME_COUNT=3;

Player::Player()
:_speed(NULL)
,_oldSpeed(NULL)
{
    
}

Player::~Player(){
    
}



bool Player::init()
{
    if (!Sprite::initWithFile("character/futsuo_000.png")) {
        return false;
    }
    
    /* アニメーションの作成 */
//    Vector<SpriteFrame *> frames;
    /* アニメ用のフレームを読み込む */
//    fileName[128] = {0};
    for(int i = 1 ; i < FRAME_COUNT ; i++ ){
        sprintf(fileName, "character/futsuo_00%d.png", i);
        auto rect  = this->getTextureRect();
        auto frame = SpriteFrame::create(fileName,rect);
        _frames.pushBack(frame);
    }
    this->setAnimation();

//    this->runAction(Animate::create(animation));
    
    /* プレイヤーの初期位置を設定 */
    this -> setPosition(Vec2(600, 1100));
    /* 剛体の設置 */
    auto material = PhysicsMaterial();
    material.friction = 0;

    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    // カテゴリをPLAYERにセットする
    body->setCategoryBitmask(static_cast<int>(Stage::TileType::PLAYER));
    // 壁とのみ衝突する
    body->setCollisionBitmask(static_cast<int>(Stage::TileType::WALL));
    // 全ての剛体の接触判定を行う
    body->setContactTestBitmask(INT_MAX);
    
    this->setPhysicsBody(body);
    this->scheduleUpdate();
    
    return true;
}
void Player::setAnimation(){
    /* スピードが変わったらアニメーションを入れる */
    if(_speed != _oldSpeed){
        
        if(_speed ==0){
            this->stopAllActions();
            /* 止まっているたびに元の画像読み出しているので遅い　TODO */
            this->setTexture("character/futsuo_000.png");
        }
        if(_speed > 0 ){
            auto animation = Animation::createWithSpriteFrames(_frames, 0.3f/getSpeed());
            animation->setRestoreOriginalFrame(true);
            this->runAction(RepeatForever::create(Animate::create(animation)));
        }
        
        this->setOldSpeed(_speed);
    }
}

void Player::update(float dt)
{
//    CCLOG("player Speed %d",this->getSpeed());
    this->setAnimation();

}