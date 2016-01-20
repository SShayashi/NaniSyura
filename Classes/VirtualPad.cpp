//
//  VirtualPad.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

//
//  VirtualPad.cpp
//  CocosProjectTest1
//
//  Created by 林　真史 on 2015/07/13.
//
//

#include "VirtualPad.h"

#define VIRTUAL_PAD_MAX_RATE 150
#define VIRTUAL_PAD_MIN_RATE 10

#define VIRTUAL_PAD_POSITION_RATE_X 1/2
#define VIRTUAL_PAD_POSITION_RATE_Y 22/100

/**
 *コンストラクタ
 */
VirtualPad::VirtualPad(){
}

/**
 *デストラクタ
 */
VirtualPad::~VirtualPad(){
}


bool VirtualPad::init(){

    if ( !Layer::init() )
    {
        return false;
    }
    //画面サイズの取得
    Size size = Director::getInstance()->getVisibleSize();
    
    //画像の生成（Pad下地）
    padBack = Sprite::create("virtualpad/virtualpad_bg.png");
    padBack->setAnchorPoint(Point(0.5f,0.5f));
    padBack->setPosition(Point(size.width*VIRTUAL_PAD_POSITION_RATE_X, size.height*VIRTUAL_PAD_POSITION_RATE_Y));
    
    /* 画像の生成（Pad操作部分） */
    padFront = Sprite::create("virtualpad/virtualpad_pad.png");
    padFront->setAnchorPoint(Point(0.5f,0.5f));
    padFront->setPosition(Point(size.width*VIRTUAL_PAD_POSITION_RATE_X, size.height*VIRTUAL_PAD_POSITION_RATE_Y));
    
    /* パッドの初期位置 */
    init_x = padFront->getPositionX();
    init_y = padFront->getPositionY();
    
    //レイヤーに追加
    this->addChild(padBack,10000);
    this->addChild(padFront,10001);
    
    //最大半径
    max_r = VIRTUAL_PAD_MAX_RATE ;
    
    //角度毎のx,y位置テーブル作成
    for(int i=0;i<360;i++){
        fsin[i]=(float)sin(i*3.1415926535/180);
        fcos[i]=(float)cos(i*3.1415926535/180);
    }

    angle = 0;
    way_x = 0;
    way_y = 0;
    now_r = 0;
    d_x = 0;
    d_y = 0;


    return true;
}

void VirtualPad::update(float dt){
    
}

/**
 *Padの表示開始
 *@param x
 *@param y
 */
void VirtualPad::startPad(int x,int y,int touch_id){
    //画面をタッチしたら描画開始
    
    /* TODO : PADの下地部分をタッチしたかどうか　(最初はpad部分をタッチしないと反応しないようにする)*/
    touchFlag = true;
    now_x = x;
    now_y = y;
    
    touchID = touch_id;
    //
//    padBack->setVisible(true);
//    padFront->setVisible(true);
//    padFront->setPosition(Point(now_x, now_y));
}

/**
 *Padの操作終了
 */
void VirtualPad::endPad(int touch_id){
    if(touch_id != touchID)return;
    
    /* データの初期化 */
    d_x = 0;
    d_y = 0;
    touchID = touch_id;
    angle = 0;
    way_x = 0;
    way_y = 0;
    now_r = 0;
    /* タッチを離したら元の位置に戻す */
    Size size = Director::getInstance()->getVisibleSize();
    padFront->setPosition(Point(size.width*VIRTUAL_PAD_POSITION_RATE_X, size.height*VIRTUAL_PAD_POSITION_RATE_Y));
}

/**
 *Padの表示更新
 *@param x
 *@param y
 */
void VirtualPad::update(int x,int y,int touch_id){
//    if(drawFlag == false)return;
    if(touch_id != touchID)return;
    //移動量
    d_x = x-init_x;
    d_y = y-init_y;
    
    //角度
    angle = atan2f(d_y, d_x);
    //cos,sin
    way_x = cosf(angle);
    way_y = sinf(angle);
    now_r =sqrt(d_x*d_x + d_y*d_y);
    //円移動範囲外か
    if ( now_r > max_r) {
        //制限後のボタン位置
        x = (int)(init_x + max_r * cos(angle));
        y = (int)(init_y + max_r * sin(angle));
        now_r = max_r;
    }
    //位置をセット
    now_x = x;
    now_y = y;
    //    padBack->setPosition(Point(init_x, init_y));
    padFront->setPosition(Point(now_x, now_y));
    
}

/**
 *cos取得
 *@return パッドの角度から算出したcos
 */
float VirtualPad::getCosX(){
    return way_x;
}

/**
 *sin取得
 *@return パッドの角度から算出したsin
 */
float VirtualPad::getSinY(){
    return way_y;
}

/**
 *バーチャルパッド使用中かどうかの取得
 *@return drawFlag trueなら表示中
 */
bool VirtualPad::isTouch(){
    return touchFlag;
}

/**
 *方向取得
 *@return int 4方向のうちどの方向かを返す.
 *方向は⬇内容で表す 5が中心
 *789
 *456
 *123
 */
int VirtualPad::get4Way(){
    
    //移動していないか
    if(d_x*d_x + d_y*d_y< VIRTUAL_PAD_MIN_RATE*VIRTUAL_PAD_MIN_RATE){
        return 5;
    }
    //上
    if(way_x<=fcos[45]&&way_x>=fcos[135]&&way_y>0){
        return 8;
    }
    //下
    if(way_x<=fcos[315]&&way_x>=fcos[225]&&way_y<0){
        return 2;
    }
    //左
    if(way_y<=fsin[135]&&way_y>=fsin[225]&&way_x<0){
        return 4;
    }
    //右
    if(way_y<=fsin[45]&&way_y>=fsin[315]&&way_x>0){
        return 6;
    }
    return -1;
}

/**
 *方向取得
 *@return int 8方向のうちどの方向かを返す.
 *方向は⬇内容で表す 5が中心
 *789
 *456
 *123
 */
int VirtualPad::get8Way(){
    //移動していないか
    if(d_x*d_x + d_y*d_y< VIRTUAL_PAD_MIN_RATE*VIRTUAL_PAD_MIN_RATE){
        return 5;
    }
    //右上
    if(way_x<=fcos[22]&&way_x>=fcos[68]&&way_y>0){
        return 9;
    }
    //上
    if(way_x<=fcos[68]&&way_x>=fcos[112]&&way_y>0){
        return 8;
    }
    //左上
    if(way_x<=fcos[112]&&way_x>=fcos[158]&&way_y>0){
        return 7;
    }
    //右下
    if(way_x<=fcos[338]&&way_x>=fcos[292]&&way_y<0){
        return 3;
    }
    //下
    if(way_x<=fcos[292]&&way_x>=fcos[248]&&way_y<0){
        return 2;
    }
    //左下
    if(way_x<=fcos[248]&&way_x>=fcos[202]&&way_y<0){
        return 1;
    }
    //左
    if(way_y<=fsin[158]&&way_y>=fsin[202]&&way_x<0){
        return 4;
    }
    //右
    if(way_y<=fsin[22]&&way_y>=fsin[338]&&way_x>0){
        return 6;
    }
    return -1;
}
/**
 *パッドの移動量からスピードを返す
 *@return スピードを返す
 */
int VirtualPad::getSpeed(){
   /* 座標用 */
    if(now_r >= 150){
        return 8;
    }
    
    if(now_r >= 110){
        return 6;
    }
    
    if(now_r >= 70){
        return 4;
    }
    
    if(now_r >= 30){
        return 2;
    }
    
    if(now_r >= 0){
        return 0;
    }
////     ここに来ることはないはず
//    CCLOG("Errorlog in VirtualPad");
//    return -1;
    /* 物理エンジンよう */
    return now_r*3;
}

/**
 *
 */
Sprite* VirtualPad::getPadBack(){
    return padBack;
}

