//
//  MobEnemy.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//


#include <stdio.h>
#include "MobEnemy.h"

USING_NS_CC;


MobEnemy::MobEnemy()
{
    
}

MobEnemy::~MobEnemy(){
    
}


bool MobEnemy::init()
{
    if (!Sprite::initWithFile("character/mobu_000.png")) {
        return false;
    }

    
    this->setTag((int)Stage::TileType::MOB_ENEMY);
    /* アニメーションを入れるならココ */
    for(int i = 1 ; i < FRAME_COUNT ; i++ ){
        sprintf(fileName, "character/mobu_00%d.png", i);
        auto rect  = this->getTextureRect();
        auto frame = SpriteFrame::create(fileName,rect);
        _frames.pushBack(frame);
    }
    this->setAnimation();

    /* 剛体の設置 */
    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    // カテゴリをMOB_MobEnemyにセットする
    body->setCategoryBitmask(static_cast<int>(Stage::TileType::MOB_ENEMY));
    
    /* 修羅場以外と衝突する ~はビット反転 */
    body->setCollisionBitmask(~static_cast<int>(Stage::TileType::SYURABA_EREA));
    // 全ての剛体の接触判定を行う
    body->setContactTestBitmask(INT_MAX);
    
    
    this->setPhysicsBody(body);
    this->scheduleUpdate();
    
    return true;
}

void MobEnemy::setAnimation(){
    /* スピードが変わったらアニメーションを入れる */
    if(_speed != _oldSpeed){
        
        if(_speed ==0){
            this->stopAllActions();
            /* 止まっているたびに元の画像読み出しているので遅い　TODO */
            this->setTexture("character/mobu_000.png");
        }
        if(_speed > 0 ){
            auto animation = Animation::createWithSpriteFrames(_frames, 0.3f/getSpeed());
            animation->setRestoreOriginalFrame(true);
            this->runAction(RepeatForever::create(Animate::create(animation)));
        }
        
        this->setOldSpeed(_speed);
    }
}


void MobEnemy::update(float dt)
{
    this->setAnimation();
}
