//
//  Enemy.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Enemy.h"
#include "Stage.h"

USING_NS_CC;

Enemy::Enemy()
:_speed(NULL)
{
    
}

Enemy::~Enemy(){
    
}


bool Enemy::init()
{
//    if (!Sprite::initWithFile("character/mobu_stop.png")) {
//        return false;
//    }
//
//    /* アニメーションを入れるならココ */
//    
//    /* 剛体の設置 */
//    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
//    // 剛体の回転を無効にする
//    body->setRotationEnable(false);
//    // カテゴリをMOB_ENEMYにセットする
//    body->setCategoryBitmask(static_cast<int>(Stage::TileType::MOB_ENEMY));
//
//    /* 修羅場以外と衝突する ~はビット反転 */
//    body->setCollisionBitmask(~static_cast<int>(Stage::TileType::SYURABA_EREA));
//    // 全ての剛体の接触判定を行う
//    body->setContactTestBitmask(INT_MAX);
//    
//
//    this->setPhysicsBody(body);
//    this->scheduleUpdate();
//    
    return true;
}

void Enemy::update(float dt)
{
   
}
