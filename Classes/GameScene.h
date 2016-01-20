//
//  GameScene.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__GameScene__
#define __SyuraProject__GameScene__

#include <stdio.h>
#include "VirtualPad.h"
#include "Stage.h"
#include "cocos2d.h"
#include "TopScroll.h"
#include "UseSqlite.hpp"
#include "SimpleAudioEngine.h"


class GameScene : public cocos2d::Layer
{
private:
    GameScene();
    virtual ~GameScene();
//    
//    /** モーダル画面のタグ
//     * TOP :トップ画面
//     * PAUSE:ポーズ画面
//     * LOSE:負け画面
//     * CLEAR:クリア画面
//     */
//    enum class ModalTag
//    {
//        TOP,
//        PAUSE,
//        LOSE,
//        CLEAR,
//    };
    
    /** ゲームの状態を表す
     * READY :開始演出
     * PLAYING :ゲーム中
     * PAUSE :ポーズ中
     * SYURABA :修羅場中
     * ENDING :終了演出
     * RESULT :結果
     * LOSE :負け
     * CLEAR :クリア
     */
    enum class GameState
    {
        READY,
        PLAYING,
        PAUSE,
        SYURABA,
        ENDING,
        LOSE,
        CLEAR,
    };
    
    /** キャラを表す
     *
     *
     *
     */
    enum class SyuraEnemys
    {
        Haruka,
        Nene,
        Risa,
        Miyu,
        Kokona,
    };
    
    //
    void onReady();
    //ゲームがプレイ状態に成った時の処理
    void onPlaying();
    //ゲームがポーズ状態になった時の処理
    void onPause();
    //ゲームが修羅場演出をしている時の処理
    void onSyuraba();
    //ゲームが終了するときの処理
    void onEnding();
    //ゲームが終了したときの処理
    void onLose();
    //ゲームをクリアしたときの処理
    void onClear();
    //readyラベルを追加する処理
    void addReadyLabel();
    //ゲームの一時停止・開始を切り替える処理
    void swichPauseFlag();
    

    float time;
    bool isPauseFlag;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt)override;
    void gameLogic(float dt);
    void onEnterTransitionDidFinish() override;
    
    Size winSize;
    
    /* タッチイベントリスナー */
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
    /* 剛体の接触イベントリスナー */
    bool onContactBegin(PhysicsContact& contact);
    bool onContactPresolve(PhysicsContact& contact);
    void onContactSeparate(PhysicsContact& contact);
    
    //同じ種類のキャラ(修羅キャラVs修羅キャラ),(Mob Vs Mob)がぶつかった時の処理
    void contactEvenEnemy(PhysicsBody *bodyA , PhysicsBody *bodyB);
    
    //修羅キャラとMobがぶつかった時の処理
    void contactSyuraAndMob(PhysicsBody *Syura , PhysicsBody *Mob);
    
    //    void onContactPostSolve(PhysicsContact& contact);衝突後
    //修羅キャラを二人渡して、勝った方を返す
    SyuraEnemy* battleSyuraEnemy(SyuraEnemy* syuraEnemyA , SyuraEnemy* syuraEnemyB);
    //修羅キャラを二人渡して、それ専用のカットイン画像のファイル名を返す
    char *getCutInFileName(SyuraEnemy* syuraEnemyA , SyuraEnemy* syuraEnemyB);
    char *getIconNameFromCutImage(char* cutfilename);
    //カットのファイル名から漫画アイコンのボタンを返す
    MenuItemImage *getIconButton(char *CutFileName);
    
    
    /* 制限時間用変数　*/
    CC_SYNTHESIZE(float, _second, Second);
    /* 現在のゲーム状態 */
    CC_SYNTHESIZE(GameState, _state, State);
    /* クリア画面での修羅場アイコンを格納する */
    CC_SYNTHESIZE(cocos2d::Vector<MenuItemImage*>,_syuraIcon, SyuraIcon);

    /* クリア画面での修羅場アイコンの名前を格納する */
    std::vector<char*> _syuraIconName;
    
    /* ステージの作成 */
    CC_SYNTHESIZE_RETAIN(Stage *, _stage, Stage);
    /* VirutalPadの生成 */
    CC_SYNTHESIZE_RETAIN(VirtualPad *, _virPad, VirtualPad);
    /* 制限時間用ラベル */
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _secondLabel, SecondLabel);
    /* sqliteのラッパークラスの作成 */
    CC_SYNTHESIZE_RETAIN(UseSqlite*, _sqlite, Sqlite);

    CREATE_FUNC(GameScene);
    
};




#endif /* defined(__SyuraProject__GameScene__) */
