//=============================================================================
//
// アイテムのインタフェース [GO_Item.h]
// Author : Yanagisawa Yuta
//
//=============================================================================
#pragma once
#include "GameObject.h"
#define ITEM_BULLET_SPEED 10.0f

enum ITEM_INDEX {
    ITEM_NONE = -1,
    ITEM_BULLET,
    ITEM_DROP_EXP_POINT,

    ITEM_MAX,
};

class GO_Item :
    public GameObject
{
private:
    static const int ITEM_NUM_MAX = 100;
    static const int REFLECT_BULLET_NUM = 3;
public:
    // GameObject を介して継承されました
    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    virtual int ReturnIndex(void) = 0;

    virtual void SetItem()=0;
    virtual void SetItem(D3DXVECTOR3 vec)=0;
    virtual void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 vec) = 0;


    GAME_OBJECT GetObjInfo(int index) { return m_Obj[index]; }

    int GetItemNumMax() { return ITEM_NUM_MAX; }
    void DeleteObj(int index) { m_Obj[index].use = false; }

    void InversionVec(int index, D3DXVECTOR3 vec) { 
        if (m_Obj[index].use == true) {            
            m_Obj[index].vec.x *= vec.x;
            m_Obj[index].vec.y *= vec.y;
            m_Obj[index].vec.z *= vec.z;
            m_Obj[index].counter++;

            if (m_Obj[index].counter >= REFLECT_BULLET_NUM) {
                DeleteObj(index);
            }
        }        
    }

    virtual void SetVec(int index, D3DXVECTOR3 vec) {
        if (m_Obj[index].use == false)return;
        m_Obj[index].vec = vec;
    }

    //  バレット　ー＞　クールタイムの最大フレーム数
    virtual void ChangeValue(int value) = 0;

    //  バレット　ー＞　クールタイム中(m_IsCoolTime)
    virtual bool GetFlag(void) = 0;

    //  ランダム(-1.0f ～ 1.0f)
    FLOAT ItemRand() {
        int index = rand() % 2;
        switch (index)
        {
        case 0:
            return frand();
            break;
        case 1:
            return -1 * frand();
            break;
        default:
            break;
        }

        return frand();
    }

protected:
    DX11_MODEL m_Model;
    GAME_OBJECT m_Obj[ITEM_NUM_MAX];
};

