//
//  Helper.hpp
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/24.
//
//

#ifndef Helper_hpp
#define Helper_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;


class Helper
{
private:
    Helper();
    static Helper* mHelper;
public:
    static Helper* getInstance();
    
    // ゲーム全体で使用したい変数
//    bool soundOn;
    int _gameFeadCount;
    int _chartBoostCount;


    // 値の初期化
    void initialize();
    
    // メソッド
    // Gamefeadの広告を表示させるかどうかの処理
    bool isGameFeadOpen();
    // ChartBoostの広告を表示させるかどうかの処理
    bool isChartBoostOpen();
    //チュートリアルすでに出ているかどうか
    CC_SYNTHESIZE(bool, _tutorialOpend, TutorialOpend);
};
#endif /* Helper_hpp */
