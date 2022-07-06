//=============================================================================
//
// ステージクリア時のエフェクト [Eff_Clear.h]
// Author : Yanagisawa Yuta
//
// 説明：クリアしたんだな。って感じのエフェクトです
//		経験値完全取得後、発動。
//		スキル選択後、発動
//=============================================================================
#pragma once
#include "GO_Effect.h"
class Eff_Clear :
    public GO_Effect
{
private:
    static const int CLEAR_X_NUM = 6;
    static const int CLEAR_Y_NUM = 8;

    const float CLEAR_WIDTH = (1.0f / static_cast<float>(CLEAR_X_NUM));
    const float CLEAR_HEIGHT = (1.0f / static_cast<float>(CLEAR_Y_NUM));

    static const int CLEAR_MAX = 45;

    char m_TexName[64] = "data/TEXTURE/Clear_Effect1.png";
    char m_TexName2[64] = "data/TEXTURE/Clear_Effect2.png";

    int m_TexIndex2 = 0;
    int m_NowTex = 0;

    float m_u, m_v;
public:
    // GO_Effect を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void SetEffect() override;

    virtual void SetEffect(D3DXVECTOR3 pos) override;

    virtual void SetEffect(bool IsStart) override;
private:
    int m_delay = 0;

    
};

