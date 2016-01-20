//
//  SyuraEnemy.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "SyuraEnemy.h"
#include "Stage.h"
SyuraEnemy::SyuraEnemy()
{
    this->setSpeed(6.5);
}

SyuraEnemy::~SyuraEnemy(){
    
}


bool SyuraEnemy::init()
{
    
    return true;
}

void SyuraEnemy::update(float dt)
{
    
}

bool SyuraEnemy::setSyuraBody(cocos2d::PhysicsBody * body){
    this->setTag((int)Stage::TileType::SYURA_ENEMY);
    /* 剛体の設置 */
//    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    // カテゴリをSYURA_ENEMYにセットする
    body->setCategoryBitmask(static_cast<int>(Stage::TileType::SYURA_ENEMY));
    
    /* 修羅場以外と衝突する ~はビット反転 */
    body->setCollisionBitmask(~static_cast<int>(Stage::TileType::SYURABA_EREA));
    // 全ての剛体の接触判定を行う
    body->setContactTestBitmask(INT_MAX);
    
    this->setPhysicsBody(body);
    return true;
}
