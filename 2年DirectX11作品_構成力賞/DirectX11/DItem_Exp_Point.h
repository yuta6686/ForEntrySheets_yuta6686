//=============================================================================
//
// モデル型のEXPポイント [DItem_Exp_Point.h]
// Author : Yanagisawa Yuta
//
// 説明：エネミー倒すと正四面体のEXPが出現します
//=============================================================================
#pragma once
#include "DropItem.h"
class DItem_Exp_Point :
    public DropItem
{
private:
    char m_TexName[64] = "data/MODEL/Experience_point.obj";

    static const int LIVE_LIMIT = 60 * 10;
public:


    // DropItem を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex(void) override;

private:
    void Move();
};

