//=============================================================================
//
// プレイヤーとエネミーの当たり判定 [PlayerAndEnemyCollision.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once

//  インクルード  //
#include "GO_Collision.h"
#include "GO_Enemy.h"
#include "GO_Player.h"
#include "fade.h"
#include "Eff_RockOn.h"
#include "Eff_Explosion.h"
#include <list>

//  マクロ定義
#define NO_RANGE 0.0f

class PlayerAndEnemyCollision :
    public GO_Collision
{
private:
    const float BULLETS_DIFFUSION = 5.0f;
public:
    PlayerAndEnemyCollision():
        m_pEnemy(nullptr),m_pPlayer(nullptr),
        m_pBullet(nullptr), m_pExpPoint(nullptr){}

    // GO_Collision を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual bool IsCollision() override { return false; };



    void SetEnemy(GO_Enemy* p) { m_pEnemy = p; }
    void SetPlayer(GO_Player* p) { m_pPlayer = p; }

private:
    GO_Enemy* m_pEnemy;
    GO_Player* m_pPlayer;

    GO_Item* m_pBullet;
    GO_Item* m_pExpPoint;

    Eff_RockOn m_RockOn;
    Eff_Explosion m_Explosion;

    int m_CollExplosionIndex = -1;
    bool m_IsColl = false;

    int m_ClearEffectCounter = 0;

    //  現在の射程を格納する
    FLOAT m_Range = 0.0f;

    //  接近しているEXPPointのインデックスを格納する
    std::list<int> ml_ExpPointIndex_Approach;

    //  接触しているExpPoiintのインデックスを格納する（通常の当たり判定)
    std::list<int> ml_ExpPointIndex_Contact;

    // GO_Collision を介して継承されました
    virtual int IsCollisions(int index) override;
    virtual void CollisionUpdate(int index) override;

    

    //  アイテム
    void ItemUpdate();
    void ItemUpdate_Bullet();

    //  pos1からpos2へのベクトル
    D3DXVECTOR3 VectorOfPlayer_Set(D3DXVECTOR3 pos1 ,D3DXVECTOR3 pos2, FLOAT speed);

    void SetDiamondVec();

    //  エネミーと弾の当たり判定
    //  第一引数：エネミーのインデックス
    //  第二引数：バレットのインデックス
    //  戻り値  ：エネミーのインデックス
    int IsCollisions_Bullets(int index, int index2);
    void CollisionUpdate_Bullet(int index, int index2);


    //  射程内の接近処理[プレイヤーと経験値]
    //  引数：射程
    //  戻値：bool
    //  機能：射程内に入ったら、プレイヤーに近づくようにする
    bool IsApproach(int index,FLOAT range);

    bool IsApproach(FLOAT range,D3DXVECTOR3 pos1, D3DXVECTOR3 pos2,FLOAT size1,FLOAT size2);

    std::list<int> InRangeEnemyIndex();

    //  経験値獲得したら次のシーンへ
    void ToNextScene();

    //  一番近いエネミーのインデックスを返す関数
    int NearestEnemy(void);

    //  一番近いエネミーに照準をあわせる
    void RockOnNearestEnemy(void);

    //  エフェクトが使われていない時の処理
    void ClearEffect(void);

    //  エネミー1体爆発
    void EnemyExplosionOnece();
};

