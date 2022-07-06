//=============================================================================
//
// バレット [Item_Bullet.h]
// Author : Yanagisawa Yuta
//
// バレットをアイテムとして管理していたが、他のアイテムを作成せずに終わってしまった。
// 
//=============================================================================
#pragma once
#include "GO_Item.h"


class Item_Bullet :
    public GO_Item
{
private:
    const int COOL_TIME_MAX_DEFAULT = 30;
public:
    // GO_Item を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex(void) override;

    void SetItem();
    void SetItem(D3DXVECTOR3 vec);


    // GO_Item を介して継承されました
    virtual void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 vec) override;

    // GO_Item を介して継承されました
    virtual void ChangeValue(int value) override 
    {
        m_CoolTimeMax -= value;
    }

    // GO_Item を介して継承されました
    virtual bool GetFlag(void) override 
    {
        return m_IsCoolTime;
    }

    bool EndOfCoolTime();

private:
    void CoolTimeManager();

    bool m_IsCoolTime;
    int m_CoolTimeMax = COOL_TIME_MAX_DEFAULT;
    int m_CoolTimeCounter;


    float m_Range;


};

