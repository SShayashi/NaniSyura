//
//  ComicListModal.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/15.
//
//

#ifndef __SyuraProject__ComicListModal__
#define __SyuraProject__ComicListModal__

#include <stdio.h>
#include "cocos2d.h"
#include "CocosGUI.h"
#include "TopScroll.h"
#include "UseSqlite.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class ComicListModal : public cocos2d::Layer
{
protected:
    // コンストラクタ
    ComicListModal();
    // デストラクタ
    virtual ~ComicListModal();
    //音処理クラスのインスタンス作成
    CocosDenshion::SimpleAudioEngine* soundEngineSE = CocosDenshion::SimpleAudioEngine::getInstance();

    
public:
    //アイコンのファイルすべて
    std::vector<std::string> _comicIds{\
        "comic_icon_haruka_win_kokona.png",
        "comic_icon_haruka_win_risa.png",
        "comic_icon_kokona_win_miyu.png",
        "comic_icon_kokona_win_risa.png",
        "comic_icon_miyu_win_haruka.png",
        "comic_icon_miyu_win_nene.png",
        "comic_icon_nene_win_haruka.png",
        "comic_icon_nene_win_kokona.png",
        "comic_icon_risa_win_miyu.png",
        "comic_icon_risa_win_nene.png"
    };
    virtual bool init();
    //
    void checkIconFlag(char* imageName,Vec2 position);
    //secret画像の追加をする
    void addSecretImage(Vec2 position);
    /* sqliteのラッパークラスの作成 */
    CC_SYNTHESIZE_RETAIN(UseSqlite*, _sqlite, Sqlite);

    CREATE_FUNC(ComicListModal);
};

#endif /* defined(__SyuraProject__ComicListModal__) */
