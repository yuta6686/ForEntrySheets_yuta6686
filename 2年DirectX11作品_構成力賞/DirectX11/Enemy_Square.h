//=============================================================================
//
// 無相の形をした立方体エネミー [Enemy_Square.h]
// Author : Yanagisawa Yuta
// 
// 説明：ランダムに動く
//=============================================================================
#pragma once
#include "GO_Enemy.h"


float Enemyfrand();
class Enemy_Square :
    public GO_Enemy
{
private:
    
public:
    // GO_Enemy を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Action() override;

    virtual bool Death() override;



    // GO_Enemy を介して継承されました
    virtual void SetEnemy() override;
    virtual void SetEnemy(D3DXVECTOR3 pos)override;
    virtual void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size)override;
    virtual void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 vec)override;
    virtual int ReturnIndex() override { return ENEMY_SQUARE; }

private:
    float m_Emission;


};

