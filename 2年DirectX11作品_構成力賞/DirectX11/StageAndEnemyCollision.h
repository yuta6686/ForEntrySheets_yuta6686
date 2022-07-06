//=============================================================================
//
// ステージとエネミーの衝突処理 [StageAndEnemyCollision.h]
// Author : Yanagisawa Yuta
//
// 説明：エネミーがステージに衝突
// ー＞エネミーのベクトルを反転
//=============================================================================
#pragma once
#include "GO_Collision.h"
#include "GO_Stage.h"
#include "GO_Enemy.h"

class StageAndEnemyCollision :
    public GO_Collision
{
public:
    StageAndEnemyCollision():m_pEnemy(nullptr),m_pStage(nullptr){}

    // GO_Collision を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    void Update();

    virtual void Draw() override;

    virtual bool IsCollision() override { return false; }
    virtual int IsCollisions(int index)override;

    virtual void CollisionUpdate(int index) override;

    void SetEnemy(GO_Enemy* p) { m_pEnemy = p; }
    void SetStage(GO_Stage* p) { m_pStage = p; }

private:
    GO_Stage* m_pStage;
    GO_Enemy* m_pEnemy;
};

