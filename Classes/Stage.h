//
//  Stage.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__Stage__
#define __SyuraProject__Stage__

#include <stdio.h>

#include "cocos2d.h"
#include "Player.h"
#include "CustomFollow.h"
#include "Enemy.h"
#include "MobEnemy.h"
#include "SyuraEnemy.h"
#include "Haruka.h"
#include "Nene.h"
#include "Miyu.h"
#include "Kokona.h"
#include "Risa.h"


class Stage :public cocos2d::Layer
{
public:

    
    /// タイルの種類
    enum class TileType {
        /// 壁
        WALL = 1 << 0,
        /// プレイヤー
        PLAYER = 1 << 1,
        /// MOBの敵キャラ
        MOB_ENEMY = 1 << 2,
        /// 修羅場を起こす敵キャラ
        SYURA_ENEMY = 1 << 3,
        /// 修羅場エリア
        SYURABA_EREA = 1 << 4
    };

    void update(float dt)override;
    //修羅場で管理するエリアに敵を追加
    void addEnemyOnSyuraba(Enemy *enemy);
    //ステージ上から敵を削除
    bool removeEnemyOnStage(Enemy *enemy);
    //修羅場発生時に実行する関数。修羅場の敵を全て削除
    bool removeEnemyOnSyuraba(cocos2d::Vector<Node*> syuraarea);
    //修羅場が起きずに敵が離れた場合の関数
    bool leaveEnemyOnSyuraba(Enemy *enemy);
    //ステージに神5のキャラを追加する処理
    bool addSyuraEnemyOnStage();
    //フィールドにモブ敵を追加
    void addEnemyOnStage();
    //敵を動かす
    void moveEnemys();

    //敵の出現場所調整のための
    int getEnemyAppearenceNum(float nowPosX,float nowPosY);
    
    /* タイルマップ */
    CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);
    /* プレイヤー */
    CC_SYNTHESIZE_RETAIN(Player *, _player, Player);
    /* 敵 */
    CC_SYNTHESIZE(cocos2d::Vector<Enemy*>,_enemys,Enemys);
    /* 修羅場エリアに入っている敵を格納する */
    CC_SYNTHESIZE(cocos2d::Vector<Node*>,_syuraarea, Syuraarea);
    /* 神5を格納する */
    CC_SYNTHESIZE(cocos2d::Vector<SyuraEnemy*>, _syuraenemys, SyuraEnemys);
    CREATE_FUNC(Stage);
    /** ステージ番号からステージを生成します
     *  @param level ステージ番号
     *  @return ステージ
     */
//    static Stage * createWithLevel(int level);
protected:
//    bool initWithLevel(int level); gmcmnmdnkg8bc
    Stage();
    virtual ~Stage();
    bool init() override;
private:
    
    /** 指定のレイヤーの特定位置のタイルに剛体を設置する
     *  指定座標にタイルがなかった場合はnullptrを返す
     *  @param layer 対象のレイヤー
     *  @param coordinate 対象タイルのあるマップ上の座標
     *  @return タイルのスプライト、またはnullptr
     */
    cocos2d::Sprite* addPhysicsBodyTMX(cocos2d::TMXLayer *layer, cocos2d::Vec2& coordinate);
    
    cocos2d::Size winSize;
    //敵の追加する位置を作成
    cocos2d::Vec2 createEnemyPosition(cocos2d::Vec2 playerPos);
    //建物を追加するメソッド
    bool addBuildings();
};


#endif /* defined(__SyuraProject__Stage__) */
