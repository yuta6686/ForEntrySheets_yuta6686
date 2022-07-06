//=============================================================================
//
// ステージ背景 [StageBackground.h]
// Author : Yanagisawa Yuta
//	説明：ステージの背景
//=============================================================================
#pragma once
#include "GO_Stage.h"
class StageBackground :
    public GO_Stage
{
private:
    static const int CIRCLE_MAX = 10;
    const float CIRCLE_LIMIT = 2000.f;
public:


    // GO_Stage を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual int ReturnIndex() override
    {
        return STAGE_NUM_001;
    }

    float StageFrand();


private:
    DX11_MODEL m_Circle_001;
    DX11_MODEL m_Circle_002;
    DX11_MODEL m_Circle_003;

    DX11_MODEL m_ToriiModel;

    GAME_OBJECT m_Circles1[CIRCLE_MAX];
    GAME_OBJECT m_Circles2[CIRCLE_MAX];
    GAME_OBJECT m_Circles3[CIRCLE_MAX];

    GAME_OBJECT m_Torii;
};

