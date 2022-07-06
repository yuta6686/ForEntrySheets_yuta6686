//=============================================================================
//
// モデル型のEXPポイント [DItem_Exp_Point.h]
// Author : Yanagisawa Yuta
//
// 説明：エネミー倒すと正四面体のEXPが出現します
//=============================================================================
#pragma once
#include "GO_Item.h"
class DropItem :
    public GO_Item
{
private:
    const float FRAND_LIMIT = 2.0f;
public:
    // GO_Item を介して継承されました
    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    virtual int ReturnIndex(void) override=0;

    
    virtual void SetItem() override 
    {
        for (int i = 0; i < GetItemNumMax(); i++) {
            if (m_Obj[i].use)continue;
            m_Obj[i].use = true;
            m_Obj[i].vec = { ItemRand()* FRAND_LIMIT,ItemRand() * FRAND_LIMIT,ItemRand() * FRAND_LIMIT };
            m_Obj[i].counter = 0;
            break;
        }
    }
    

    virtual void SetItem(D3DXVECTOR3 pos) override {
        for (int i = 0; i < GetItemNumMax(); i++) {
            if (m_Obj[i].use)continue;
            m_Obj[i].use = true;
            m_Obj[i].vec = { ItemRand() * FRAND_LIMIT,ItemRand() * FRAND_LIMIT,ItemRand() * FRAND_LIMIT };
            m_Obj[i].pos = pos;
            m_Obj[i].counter = 0;
            break;
        }
    }

    virtual void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 vec) override {
        for (int i = 0; i < GetItemNumMax(); i++) {
            if (m_Obj[i].use)continue;
            m_Obj[i].use = true;
            m_Obj[i].vec = { ItemRand() * FRAND_LIMIT,ItemRand() * FRAND_LIMIT,ItemRand() * FRAND_LIMIT };
            m_Obj[i].pos = pos;
            m_Obj[i].vec = vec;
            m_Obj[i].counter = 0;
            break;
        }
    };

    virtual void ChangeValue(int value) override {}

    virtual bool GetFlag(void) override { return false; }


};

