#pragma once
#include "GameObject.h"
#include "E_Circle.h"
#include "E_SpeedUp.h"
#include "GO_SS_Effect_Wind.h"

class GO_SS_Karashi :
    public GameObject
{
private:
    static const int KARASHI_MAX = 30;
public:
    // GameObject を介して継承されました
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override;

    //	キッチンタイマーの情報取得
    VERTEX_T* GetKarashi(int index) { return &m_Karashi[index]; }

    //	キッチンタイマーの最大数取得
    int GetNegiMax() { return KARASHI_MAX; }

    //	Useフラグのセッター
    void SetUse(int index, bool flag) { m_Karashi[index].use = flag; }

    //	動き
    void AddX(FLOAT x);

    
    void SetEffect(D3DXVECTOR2 pos) {
        m_Circle.SetEffectNoMouse(m_Karashi->pos, 100.0f);
        m_Circle_001.SetEffectNoMouse(m_Karashi->pos, 0.0f);
        m_SpeedUp.SetEffectNoMouse(pos);
        m_wind.SetWindMoveEff(5);
    }

    void SetKarashi(D3DXVECTOR2 pos);

    void SetEffectPos(D3DXVECTOR2 pos) {
        m_SpeedUp.SetPos(pos);
    }

private:

    E_Circle m_Circle;
    E_Circle m_Circle_001;
    E_SpeedUp m_SpeedUp;
    GO_SS_Effect_Wind m_wind;

    //  頂点情報
    VERTEX_T m_Karashi[KARASHI_MAX];

    //  テクスチャ用
    int m_TexIndex;
    char* m_pTexName = "data/TEXTURE/karashi.png";
};

