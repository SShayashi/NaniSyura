//
//  VirtualPad.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//
#ifndef CocosProjectTest1_VirtualPad_h
#define CocosProjectTest1_VirtualPad_h

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

/**
 *VirtualPadクラス.
 */
class VirtualPad :public::Layer {
private:
    /*コンストラクタ*/
    VirtualPad();
    /*デストラクタ*/
    ~VirtualPad();
    //Pad下地
    Sprite* padBack;
    //Pad
    Sprite* padFront;
    //表示フラグ
    bool touchFlag;
    //Padの初期位置
    int init_x;
    int init_y;
    //現在位置
    int now_x;
    int now_y;
    //移動量
    int d_x;
    int d_y;
    //移動sin,cos
    float way_x;
    float way_y;
    //最大半径
    int max_r;
    //現在の半径
    int now_r;
    //角度
    float angle;
    //角度テーブル
    float fsin[360];
    float fcos[360];
    //タッチID
    int touchID;
    
public:
    
    void update(float dt)override;
    CREATE_FUNC(VirtualPad);
    bool init() override;

    void startPad(int x,int y,int touch_id);
    void endPad(int touch_id);
    void update(int x,int y,int touch_id);
    float getCosX();
    float getSinY();
    bool isTouch();
    int get4Way();
    int get8Way();
    int getSpeed();
    Sprite* getPadBack();
    
};

#endif
