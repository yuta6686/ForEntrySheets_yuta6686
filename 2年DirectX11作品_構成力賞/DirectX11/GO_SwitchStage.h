//=============================================================================
//
// ステージ切り替え [GO_SwitchStage.h]
// Author : Yanagisawa Yuta
//
// 説明：ステージを切り替えます。
// 使わなかった。
//=============================================================================
#pragma once
#include "GameObject.h"
#include "StageFactory.h"
class GO_SwitchStage :
    public GameObject
{
private:
    static const int STAGE_MAX = 3;
    int m_nowStageIndex = STAGE_NUM_001;
public:
    GO_SwitchStage();
    ~GO_SwitchStage();

    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    GO_Stage* GetStage() { return m_pStage[m_nowStageIndex-1]; }

private:

    void Register(GO_Stage* pStage);
    void Create();

    StageFactory m_StageFactory;

    GO_Stage* m_pStage[STAGE_MAX];
    GO_Stage* m_pNowStage;
};

