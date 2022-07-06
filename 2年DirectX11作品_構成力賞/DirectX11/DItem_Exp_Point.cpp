//=============================================================================
//
// モデル型のEXPポイント [DItem_Exp_Point.cpp]
// Author : Yanagisawa Yuta
//
// 説明：エネミー倒すと正四面体のEXPが出現します
//=============================================================================
#include "DItem_Exp_Point.h"
#include "CoordinateTransformation.h"

void DItem_Exp_Point::Init()
{
    LoadModel(m_TexName, &m_Model);

    for (int i = 0; i < GetItemNumMax(); i++) 
    {
        m_Obj[i].pos = { 0.0f,0.0f,0.0f };
        m_Obj[i].vec = { 0.0f,0.0f,0.0f };

        float scale = 2.5f;
        m_Obj[i].scl = { scale,scale,scale };
        m_Obj[i].size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
        m_Obj[i].use = false;

        m_Obj[i].counter = 0;

    }
}

void DItem_Exp_Point::Uninit()
{
}

void DItem_Exp_Point::Update()
{
    Move();

    for (int i = 0; i < GetItemNumMax(); i++)
    {
        if (m_Obj[i].use == false)continue;

        if (m_Obj[i].counter >= LIVE_LIMIT) {
            m_Obj[i].counter = 0;
            m_Obj[i].use = false;
        }
        else {
            m_Obj[i].counter++;
        }
        
    }
}

void DItem_Exp_Point::Draw()
{
    for (int i = 0; i < GetItemNumMax(); i++)
    {
        if (m_Obj[i].use == false)continue;

        CoordinateTransformation(&m_Obj[i]);

        DrawModel(&m_Model);
    }
}

int DItem_Exp_Point::ReturnIndex(void)
{
    return ITEM_DROP_EXP_POINT;
}

void DItem_Exp_Point::Move()
{
    for (int i = 0; i < GetItemNumMax(); i++) {
        if (m_Obj[i].use == false)continue;

        m_Obj[i].pos += m_Obj[i].vec;
    }
}
