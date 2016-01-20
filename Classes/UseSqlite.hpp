//
//  UseSqlite.hpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/12/14.
//
//

#ifndef UseSqlite_hpp
#define UseSqlite_hpp
#include <iostream>
#include "cocos2d.h"
#include "sqlite/sqlite3.h"

class UseSqlite : public cocos2d::Layer
{
    
public:
    // コンストラクタ
    UseSqlite();
    // デストラクタ
    virtual ~UseSqlite();

    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(UseSqlite);
    

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
    /*いい感じのラッパー見つからないから自作する*/
    //DBを開いた時のハンドラーを返す
    int openDB();
    
    //渡された画像ファイル名が開放されているかどうかをチェック
    int isOpenImage(char* imageName);
    //渡された画像ファイル名を開放する
    void openImage(char* imageName);
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    //sqlite3
    sqlite3* useDataBase = NULL;
    char* errorMessage = NULL;
    
};
#endif /* UseSqlite_hpp */
