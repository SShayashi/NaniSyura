//
//  Stage.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Stage.h"
USING_NS_CC;
int  MAX_ENEMY_SPEED = 4;
auto enemyAppearancePos = Vec2(1500,  1500);
Stage::Stage()
:_tiledMap(nullptr)
,_player(nullptr)
{
    
}
Stage::~Stage()
{
    CCLOG("player :%d",_player->getReferenceCount());
    //    CC_SAFE_RELEASE_NULL(_tiledMap);
    CC_SAFE_RELEASE_NULL(_player);
}

bool Stage::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    /* マップファイルからノードを作成 */
    auto map = TMXTiledMap::create("map/stage3.tmx");
    this->addChild(map);
    this->setTiledMap(map);
    
    /*　地形レイヤーを取得 */
    //    auto terrainLayer = map->getLayer("Tile");
    // オブジェクトレイヤーを取得する
//    auto objectLayer = map->getLayer("Object");
    
    // 修羅場レイヤーを取得
    auto syurabaLayer = map->getLayer("Syuraba");
    
    // マップのサイズ
    auto mapSize = map->getMapSize();
       for (int i = 0; i < mapSize.width; i++) {
        for (int j = 0; j < mapSize.height; j++) {
            auto coordinate = Vec2(i, j);
            //            this->addPhysicsBody(terrainLayer, coordinate);
//            this->addPhysicsBodyTMX(objectLayer, coordinate);
            this->addPhysicsBodyTMX(syurabaLayer, coordinate);
        }
    }
    
    /* プレイヤーの設置 */
    auto player = Player::create();
    this->addChild(player,10000);
    this->setPlayer(player);
    
    /* 建物の設置 */
    Stage::addBuildings();
    /* プレイヤーに画面を追従させる */
    winSize = Director::getInstance()->getWinSize();
    /*Rectは追従する範囲を決めている Rectは左下を原点としている*/
    
   
    
    this ->runAction(CustomFollow::create(player,Rect(0, 0, _tiledMap->getContentSize().width, _tiledMap->getContentSize().height) ));
    /* x軸だけ、y軸だけと指定をする場合　この場合だとマップの範囲が扱えない */
    //    CustomFollowType type = kCustomFollowNone;
    //    this ->runAction(CustomFollow::create(player,type));
    
    /* 神5たちをベクターに格納していく */
    auto haruka = Haruka::create();
    auto nene = Nene::create();
    auto risa = Risa::create();
    auto kokona = Kokona::create();
    auto miyu = Miyu::create();
    
    _syuraenemys.pushBack(haruka);
    _syuraenemys.pushBack(nene);
    _syuraenemys.pushBack(risa);
    _syuraenemys.pushBack(kokona);
    _syuraenemys.pushBack(miyu);
    
    this->scheduleUpdate();
    
    return true;
}

/** tmxファイルからステージを読み込んで画像を配置
 *@param layer TMXファイルから読み込んだレイヤー
 *@param coordinate
 *@return マップから読み込んだ画像
 */
Sprite* Stage::addPhysicsBodyTMX(cocos2d::TMXLayer *layer, cocos2d::Vec2 &coordinate){
    /*タイルのスプライトを取り出す*/
    auto sprite = layer -> getTileAt(coordinate);
    if(sprite){
        /* 剛体用のマテリアル */
        auto material = PhysicsMaterial();
        /* 引っかからないように摩擦をゼロに */
        material.friction = 0;
        material.restitution = 0.1;
        /* 剛体を設置 */
        auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(),material);
        /* 剛体を固定する */
        physicsBody->setDynamic(false);
        /* 剛体をつけるSpriteのアンカーポイントを中心にする */
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        /* タイルのIDを取り出す */
        auto gid = layer->getTileGIDAt(coordinate);
        /* タイルのプロパティをmapで取り出す */
        auto properties = _tiledMap->getPropertiesForGID(gid).asValueMap();
        /* "category"というプロパティが存在しているかチェック */
        if(properties.count("category") > 0){
            /* プロパティのなっからcategoryの値をintとして取り出す */
            auto category = properties.at("category").asInt();
            /* 剛体にカテゴリーをセットする */
            physicsBody->setCategoryBitmask(category);
            /* 剛体と接触判定をとるカテゴリを指定する  ここではプレイヤーと敵*/
            physicsBody->setContactTestBitmask((int)Stage::TileType::PLAYER + (int)Stage::TileType::MOB_ENEMY+(int)Stage::TileType::SYURA_ENEMY);
        }
        /* 剛体をSpriteに付ける */
        sprite->setPhysicsBody(physicsBody);
        return sprite;
    }
    return nullptr;
}

/*
 *敵をマップに配置
 *@return 配置した敵のSpriteクラスを返す
 *
 */
void Stage::addEnemyOnStage(){
    auto enemy = MobEnemy::create();
    Vec2  nowPos = _player->getPosition();
    /* 要リファクタリングTODO */
    Vec2 pos = Vec2(100,100);
    
    /* 敵を配置する場所を指定 */
    /* プレイヤーからある程度離れた位置に敵追加する */
    auto addEnemyPos0 = nowPos + Vec2(0,winSize.height/2) + pos;
    auto addEnemyPos1 = nowPos + Vec2(winSize.width/2,0)+ pos;
    auto addEnemyPos2 = nowPos + winSize/2 + pos;
    auto addEnemyPos3 = nowPos - Vec2(0,winSize.height/2) - pos;
    auto addEnemyPos4 = nowPos - Vec2(winSize.width/2,0) - pos;
    auto addEnemyPos5 = nowPos - winSize/2 - pos;
    
  
    
    /* 敵の初期値を設定 */
    switch (getEnemyAppearenceNum(_player->getPositionX(),_player->getPositionY()))
    {
        case 0:
            /* 敵の初期位置 */
            enemyAppearancePos = addEnemyPos0;
            CCLOG("0地点");
            break;
        case 1:
            enemyAppearancePos = addEnemyPos1;
            CCLOG("1地点");
            break;
        case 2:
            enemyAppearancePos = addEnemyPos2;

            CCLOG("2地点");
            break;
        case 3:
            enemyAppearancePos = addEnemyPos3;
            CCLOG("3地点");
            break;
        case 4:
            enemyAppearancePos = addEnemyPos4;
            CCLOG("4地点");
            break;
        case 5:
            enemyAppearancePos = addEnemyPos5;
            CCLOG("5地点");
            break;
        default:
            /* ここに来ることはないはず */
            CCLOG("デフォルト");
            break;
    }
    enemy->setPosition(enemyAppearancePos);
    //    /* x軸のランダムな位置 */
    //    float enemyXPos = rand() % static_cast<int>(winSize.width);
    //    auto enemySize = enemy -> getContentSize();
    //
    //    /* 敵の初期位置 */
    //    enemy->setPosition(Vec2(enemyXPos,winSize.height - enemySize.height/2.0 - 40));
    /* 速度の設定 */
    enemy->setSpeed((int)rand()%MAX_ENEMY_SPEED + 1);
    
    /* ステージに敵を追加 */
    this -> addChild(enemy,2000);
    /* _enemyベクターに敵を追加する */
    _enemys.pushBack(enemy);
    
    return ;
}

/** フィールドの敵を移動
 *
 */
void Stage::moveEnemys(){
    
    for (const auto& enemy : _enemys)
    {
        
        /* 現在の敵の座標を取得 */
        Vec2 Epos = enemy->getPosition();
        /* 現在のプレイヤーの座標を取得する */
        Vec2 Ppos = _player->getPosition();
        
        /* プレイヤーとの座標の差をベクトルで取得 */
        Vec2 delta = Ppos - Epos;
        /* 角度を算出 */
        auto angle = atan2f(delta.y, delta.x);
        /* 動作量 */
        float enemyMoveX =  cosf(angle)*enemy->getSpeed();
        float enemyMoveY =  sinf(angle)*enemy->getSpeed();
        
        /* 新しい座標へセット */
        Vec2 newPosition = Vec2(enemy->getPositionX() + enemyMoveX, enemy->getPositionY() + enemyMoveY);
        
        /* マップの敵へ反映 */
        enemy->setPosition(newPosition);
        /*物理エンジンで反映 おそらくめり込まないようにするには物理エンジンでする必要がある、しかし現状では完成を急ぐため座標で移動*/
        //        enemy->getPhysicsBody()->setVelocity(enemy->getSpeed()*delta/(delta.length()));
        /* マップ外へ出ないように丸める */
        auto position = enemy->getPosition().getClampPoint(Vec2(0,0), this->getTiledMap()->getContentSize());
        enemy->setPosition(position);
    }
    //    auto iterator = _enemys.begin();
    //    while (iterator != _enemys.end()) {
    //        Enemy* enemy = (Enemy*)(*iterator);
    //
    //        /* 現在の敵の座標を取得 */
    //        Vec2 Epos = enemy->getPosition();
    //        /* 現在のプレイヤーの座標を取得する */
    //        Vec2 Ppos = _player->getPosition();
    //
    //        /* プレイヤーとの座標の差をベクトルで取得 */
    //        Vec2 delta = Ppos - Epos;
    //        /* 角度を算出 */
    //        auto angle = atan2f(delta.y, delta.x);
    //        /* 動作量 */
    //        float enemyMoveX =  cosf(angle)*enemy->getSpeed();
    //        float enemyMoveY =  sinf(angle)*enemy->getSpeed();
    //
    //        /* 新しい座標へセット */
    //        Vec2 newPosition = Vec2(enemy->getPositionX() + enemyMoveX, enemy->getPositionY() + enemyMoveY);
    //
    //        /* マップの敵へ反映 */
    //        enemy->setPosition(newPosition);
    //        /*物理エンジンで反映 おそらくめり込まないようにするには物理エンジンでする必要がある、しかし現状では完成を急ぐため座標で移動*/
    ////        enemy->getPhysicsBody()->setVelocity(enemy->getSpeed()*delta/(delta.length()));
    //        /* マップ外へ出ないように丸める */
    //        auto position = enemy->getPosition().getClampPoint(Vec2(0,0), this->getTiledMap()->getContentSize());
    //        enemy->setPosition(position);
    //
    //        iterator++;
    //
    //    }
    return;
    
}

/** フィールドの敵を削除
 *@param *enemy 削除する敵
 *@return bool 削除できたかどうか
 */
bool Stage::removeEnemyOnStage(Enemy *enemy){
    
    /* _enemysにenemyが含まれているかを確認しておく*/
    if(_enemys.contains(enemy)){
        /* 親ノード(GameScene)から削除 */
        CCLOG("Remove Now enemy%d",enemy->getReferenceCount());
        /* 配列からも削除 */
        _enemys.eraseObject(enemy);
        CCLOG("Remove Now enemy%d",enemy->getReferenceCount());
        //        enemy->removeFromParent();
        enemy->removeFromParent();
        CCLOG("Remove Now enemy%d",enemy->getReferenceCount());
        
        return  true;
    }
    return false;
}


/** 修羅場発生時に実行すし、修羅場エリアに存在する敵を全て削除
 *  同時にステージ上に存在する敵も削除する
 *@return bool 削除できたかどうか
 */
bool Stage::removeEnemyOnSyuraba(cocos2d::Vector<Node*> syuraarea){
    /* 修羅場エリアに存在する敵を削除する */
    for (const auto& Node : syuraarea)
    {
        Enemy *enemy = dynamic_cast<Enemy*>(Node);
        /* 修羅場エリアからもenemyを削除 */
        syuraarea.eraseObject(enemy);
        /* ステージ上から敵を削除 */
        if( this->removeEnemyOnStage(enemy) == false){
            return false;
        }
        
    }
    return true;
}

/** 修羅場が発生せずに、敵が修羅場エリアを離れた時に実行
 *  離れた敵を修羅場エリアの管理するベクターから削除
 *@param enemy 修羅場から離れた敵
 *@return bool 削除できたかどうか
 */
bool Stage::leaveEnemyOnSyuraba(Enemy *enemy){
    /* _syurabaareaにenemyが含まれているかを確認しておく*/
    if(_syuraarea.contains(enemy)){
        /* 入れるからのみ削除 */
        _enemys.eraseObject(enemy);
        return  true;
    }
    return false;
}

/** 渡されたプレイヤーの位置情報をもとに敵の追加位置を決めるTODO
 *
 *@param player
 *@return bool 削除できたかどうか
 */
Vec2 Stage::createEnemyPosition(Vec2 playerPos){
    return nullptr;
}

/**
 * 建物（剛体）を設置するメソッド
 */
bool Stage::addBuildings(){
    
    //左上の横長の建物列の画像
    auto build_left_top=Sprite::create("stage/build_long_2_2.png");
    //位置を設定
    build_left_top->setPosition(Vec2(0,2120));
    CCLOG("heigt : %f ¥n widht : %f",winSize.height,winSize.width);
    //接触判定を円で生成 (半径:画像サイズの半分)
    auto build_left_top_body = PhysicsBody::createBox(build_left_top->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    build_left_top_body->setDynamic(false);
    //物理法則を画像に適用させる
    build_left_top->setPhysicsBody(build_left_top_body);
    //貼り付け
    this->addChild(build_left_top,1);
    
    //右上の横長の建物列
    auto build_right_top=Sprite::create("stage/build_long_2_1.png");
    //位置を設定
    build_right_top->setPosition(Vec2(2300,2120));
    CCLOG("heigt : %f ¥n widht : %f",winSize.height,winSize.width);
    auto build_right_top_body = PhysicsBody::createBox(build_right_top->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    build_right_top_body->setDynamic(false);
    //物理法則を画像に適用させる
    build_right_top->setPhysicsBody(build_right_top_body);
    //貼り付け
    this->addChild(build_right_top,2);

    //左下の横長の建物列
    auto build_left_bottom=Sprite::create("stage/build_long_2_1.png");
    //基準を画像の左下に
    build_left_bottom->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //位置を設定
    build_left_bottom->setPosition(Vec2(0,350));
    CCLOG("heigt : %f ¥n widht : %f",winSize.height,winSize.width);
    auto build_left_bottom_body = PhysicsBody::createBox(build_left_bottom->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    build_left_bottom_body->setDynamic(false);
    //物理法則を画像に適用させる
    build_left_bottom->setPhysicsBody(build_left_bottom_body);
    //貼り付け
    this->addChild(build_left_bottom,3);
   
    //右下の横長の建物列
    auto build_right_bottom=Sprite::create("stage/build_long_1_1.png");
    //基準を画像の左下に
    build_right_bottom->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //位置を設定
    build_right_bottom->setPosition(Vec2(2200,350));
    CCLOG("heigt : %f ¥n widht : %f",winSize.height,winSize.width);
    auto build_right_bottom_body = PhysicsBody::createBox(build_right_bottom->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    build_right_bottom_body->setDynamic(false);
    //物理法則を画像に適用させる
    build_right_bottom->setPhysicsBody(build_right_bottom_body);
    //貼り付け
    this->addChild(build_right_bottom,4);


    
    /* これ以降は小さな建物 */
    
    auto build01=Sprite::create("stage/build_1.png");
    //基準を画像の左下に
    build01->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //位置を設定
    build01->setPosition(Vec2(700,1550));
    auto body01 = PhysicsBody::createBox(build01->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    body01->setDynamic(false);
    //物理法則を画像に適用させる
    build01->setPhysicsBody(body01);
    //貼り付け
    this->addChild(build01,5);
    
    auto build02=Sprite::create("stage/build_5.png");
    //基準を画像の左下に
    build02->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //位置を設定
    build02->setPosition(Vec2(1100,900));
    auto body02 = PhysicsBody::createBox(build02->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    body02->setDynamic(false);
    //物理法則を画像に適用させる
    build02->setPhysicsBody(body02);
    //貼り付け
    this->addChild(build02,6);
    
    auto build03=Sprite::create("stage/build_4.png");
    //基準を画像の左下に
    build03->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //位置を設定
    build03->setPosition(Vec2(2000,1550));
    auto body03 = PhysicsBody::createBox(build03->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    body03->setDynamic(false);
    //物理法則を画像に適用させる
    build03->setPhysicsBody(body03);
    //貼り付け
    this->addChild(build03,7);

    auto build04=Sprite::create("stage/build_2.png");
    //基準を画像の左下に
    build04->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //位置を設定
    build04->setPosition(Vec2(2100,900));
    auto body04 = PhysicsBody::createBox(build04->getContentSize());
    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    body04->setDynamic(false);
    //物理法則を画像に適用させる
    build04->setPhysicsBody(body04);
    //貼り付け
    this->addChild(build04,8);


    
    
    return true;
}

/** ベクターからランダムに選んだ神5をステージに追加
 *
 *@param player
 *@return bool 削除できたかどうか
 */
bool Stage::addSyuraEnemyOnStage(){
    
    /* 修羅場エリアの中からランダム選択 */
    auto syuraenemy =  _syuraenemys.getRandomObject();
    if(syuraenemy == nullptr){
        return false;
    }
    
    /* 適当に位置を設定　要 TODO →　雑魚キャラと共通 */
    syuraenemy->setPosition(enemyAppearancePos);
    
    /* ステージに追加しenemyベクターにも追加 */
    this->addChild(syuraenemy,1000);
    _enemys.pushBack(syuraenemy);
    
    /* 最後は元のベクターから削除 */
    _syuraenemys.eraseObject(syuraenemy);
    
    return true;
}

int Stage::getEnemyAppearenceNum(float nowPosX,float nowPosY)
{
    int enemyPos = rand()%6;
    auto mapSizeWidth = _tiledMap->getContentSize().width;
    auto mapSizeHeight = _tiledMap->getContentSize().height;

    
    if(mapSizeWidth * 0.2 > nowPosX && enemyPos == 4){
        enemyPos = 1;
    }else if(mapSizeWidth * 0.8 < nowPosX && enemyPos == 1){
        enemyPos = 4;
    }
    
    if(mapSizeHeight * 0.5 > nowPosY && (enemyPos == 5 || enemyPos == 3)){
        enemyPos = 0;
    }
    else if(mapSizeHeight * 0.8 < nowPosY && enemyPos == 0){
        enemyPos = 3;
    }
    
    return enemyPos;

}

void Stage::update(float dt)
{
}