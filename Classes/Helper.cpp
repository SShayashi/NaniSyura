//
//  Helper.cpp
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/24.
//
//

#include "Helper.hpp"
USING_NS_CC;
#define GameFeadOpneNum 2
#define ChartBoostOpenNum 2

Helper* Helper::mHelper = NULL;

Helper::Helper()
{
    
}

Helper* Helper::getInstance()
{
    if(mHelper == NULL)
    {
        mHelper = new Helper();
        mHelper->initialize();
    }
    
    return mHelper;
}

// 値の初期化
void Helper::initialize()
{
    _gameFeadCount=0;
    _chartBoostCount=0;
    
}

#pragma mark Music

// chartboostの広告を表示させるかどうかの処理
bool Helper::isChartBoostOpen()
{
    if(_gameFeadCount == GameFeadOpneNum){
        _gameFeadCount=0;
        return true;
    }else{
        _gameFeadCount++;
        return false;
    }
}

// gamefeadの広告を表示させるかどうかの処理
bool Helper::isGameFeadOpen()
{
    if(_chartBoostCount == ChartBoostOpenNum){
        _chartBoostCount=0;
        return true;
    }else{
        _chartBoostCount++;
        return false;
    }
}