//
//  Mobu.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "Mobu.h"
USING_NS_CC;
/// アニメーションが何フレームあるか
const int FRAME_COUNT = 4;

Mobu::Mobu()
{
    
}

Mobu::~Mobu(){
    
}


bool Mobu::init()
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
    //    // カテゴリをMOB_Mobuにセットする
    //    body->setCategoryBitmask(static_cast<int>(Stage::TileType::MOB_Mobu));
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

void Mobu::update(float dt)
{
    
}
