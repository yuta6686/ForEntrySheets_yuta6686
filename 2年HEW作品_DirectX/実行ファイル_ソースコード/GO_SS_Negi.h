#pragma once
#include "GameObject.h"
#include "E_Circle.h"
class GO_SS_Negi :
    public GameObject
{
private:
    static const int NEGI_MAX = 30;
public:
    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override;

    //	キッチンタイマーの情報取得
    VERTEX_T* GetNegi(int index) { return &m_Negi[index]; }

    //	キッチンタイマーの最大数取得
    int GetNegiMax() { return NEGI_MAX; }

    //	Useフラグのセッター
    void SetUse(int index, bool flag) { m_Negi[index].use = flag; }

    //	動き
    void AddX(FLOAT x);

    void SetEffect(D3DXVECTOR2 pos) {
        m_Circle.SetEffectNoMouse(pos, 100.0f);
        m_Circle_001.SetEffectNoMouse(pos, 0.0f);
    }

    void SetNegi(D3DXVECTOR2 pos);

private:

    E_Circle m_Circle;
    E_Circle m_Circle_001;
    
    //  頂点情報
    VERTEX_T m_Negi[NEGI_MAX];

    //  テクスチャ用
    int m_TexIndex;
    char* m_pTexName = "data/TEXTURE/negi1.png";
};

