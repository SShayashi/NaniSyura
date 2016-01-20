//
//  CustomFollow.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/22.
//
//

#include "CustomFollow.h"
USING_NS_CC;

CustomFollow::CustomFollow(){
    _type = kCustomFollowNone;
    _marginRect = Rect::ZERO;
}

CustomFollow::~CustomFollow(){
    CC_SAFE_RELEASE(_followedNode);
}

CustomFollow* CustomFollow::create(Node* followNode){
    CustomFollow *follow = new CustomFollow();
    if (follow && follow->initWithTarget(followNode, Rect::ZERO))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, CustomFollowType type){
    CustomFollow *follow = new CustomFollow();
    follow->_type = type;
    if (follow && follow->initWithTarget(followNode, Rect::ZERO))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, Rect marginRect){
    CustomFollow *follow = new CustomFollow();
    follow->_marginRect = marginRect;
    /* Rectを投げればその範囲で追従をする */
    if (follow && follow->initWithTarget(followNode,follow ->_marginRect))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

void CustomFollow::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    
    if(_boundarySet)
    {
//        CCLOG("HAHAHAH");
        // whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
        if(_boundaryFullyCovered)
        {
            return;
        }
        auto winSize = Director::getInstance()->getVisibleSize();
        Vec2  newTargetPos = _halfScreenSize + Vec2(0, (winSize.height-640)/2);
        Vec2 tempPos = newTargetPos - _followedNode->getPosition();
//        CCLOG("現在の位置　x座標　：%f",tempPos.x);
//        CCLOG("現在の位置　y座標　：%f",tempPos.y);
        _target->setPosition(clampf(tempPos.x, _leftBoundary, _rightBoundary),
                             clampf(tempPos.y, _bottomBoundary, _topBoundary));
//        CCLOG("左　:%f",_leftBoundary);
//        CCLOG("右　:%f",_rightBoundary);
//        CCLOG("した :%f",_bottomBoundary);
//        CCLOG("上　：%f",_topBoundary);
//        CCLOG("現在の位置　x座標　：%f",clampf(tempPos.x, _leftBoundary, _rightBoundary));
//        CCLOG("現在の位置　y座標　：%f",clampf(tempPos.y, _bottomBoundary, _topBoundary));
    }
    else
    {
        _target->setPosition(_halfScreenSize - _followedNode->getPosition());
    }

////    Trueだと追従しない
////    setBoundarySet(true);
//    CC_UNUSED_PARAM(dt);
//    /* 定められたエリアの限界に位置しているかどうか？ */
//    if(_boundarySet)
//    {
//        /* 移動範囲が画面より小さかったときは、画面を追従させない */
//        if(_boundaryFullyCovered)
//            return;
//        /* halfScreenSizeが基準となっている？ */
//        Point tempPos = _halfScreenSize - _followedNode->getPosition();
//        /* 現在のx,yの座標を最小値最大に丸めている  */
//        float x = clampf(tempPos.x, _leftBoundary, _rightBoundary);
//        float y = clampf(tempPos.y, _bottomBoundary, _topBoundary);
//        
//        /* Xだけ動かす場合はyは固定にする */
//        if(_type == kCustomFollowXOnly){
//            y = _target->getPositionY();
//        }
//        /* Yだけ動かす場合はxは固定にする */
//        else if (_type == kCustomFollowYOnly){
//            x = _target->getPositionX();
//        }
//        CCLOG("HELLOWWW");
//        _target->setPosition(Point(x , y));
//        
//    }
//    else
//    {
//        CCLOG("ELSE HELOOWWW");
//        Point calcPos = _target->convertToWorldSpace(_followedNode->getPosition());
//        
//        if(_marginRect.containsPoint(calcPos)){
//            return;
//        }
//        
//        float x = _halfScreenSize.x - _followedNode->getPositionX();
//        float y = _halfScreenSize.y - _followedNode->getPositionY();
//        
//        if(_type == kCustomFollowXOnly){
//            y = _target->getPositionY();
//        }
//        else if (_type == kCustomFollowYOnly){
//            x = _target->getPositionX();
//        }
//        
//        _target->setPosition(Point(x , y));
//    }
}