//=============================================================================
//
// ダイヤモンド型のエネミー [Enemy_Diamond.h]
// Author : Yanagisawa Yuta
//
// 説明：プレイヤーを追いかけるように動きます
//=============================================================================
#pragma once
#include "GO_Enemy.h"
class Enemy_Diamond :
    public GO_Enemy
{
public:
    // GO_Enemy を介して継承されました
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Action() override;
    virtual bool Death() override;
    virtual void SetEnemy() override;
    virtual void SetEnemy(D3DXVECTOR3 pos)override;
    virtual void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size)override;
    virtual void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 vec)override;

    virtual int ReturnIndex() override { return ENEMY_DIAMOND; }

private:
    float m_Emission;


};

