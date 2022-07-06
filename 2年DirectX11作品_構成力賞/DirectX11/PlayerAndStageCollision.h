//=============================================================================
//
// プレイヤーとステージの衝突処理 [PlayerAndStage.h]
// Author : Yanagisawa Yuta
//
// 説明：プレイヤーがステージに衝突すると緩やかに戻されていく
//=============================================================================
#pragma once
#include "GO_Collision.h"
#include "GO_Stage.h"
#include "GO_Player.h"

class PlayerAndStageCollision :
    public GO_Collision
{
private:
    const float REFLECT_ACCELERATION = 0.1f;
    const float REFLECT_DEFAULT_SPEED = 1.0F;
    const float REFLECT_MAX = 50.0f;
public:
    PlayerAndStageCollision() :m_pStage(nullptr), m_pPlayer(nullptr) {}

    // GO_Collision を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual bool IsCollision() override;

    virtual int IsCollisions(int index) override;

    virtual void CollisionUpdate(int index) override;

    void CollisionUpdate();


    void SetPlayer(GO_Player* p) { m_pPlayer = p; }
    void SetStage(GO_Stage* p) { m_pStage = p; }

private:
    GO_Stage* m_pStage;
    GO_Player* m_pPlayer;
    GO_Item* m_pItem;

    D3DXVECTOR3 m_playerVec;
    D3DXVECTOR3 m_pre;

    D3DXVECTOR3 m_ItemVec;

    float   m_Reflect;
    int     m_Reflect_Counter;

    void Update_PAS_Reflect();

    void Update_Reflect_IsColl();
    void Update_Reflect_NoColl();

    void Update_IAS_Reflect();
};

