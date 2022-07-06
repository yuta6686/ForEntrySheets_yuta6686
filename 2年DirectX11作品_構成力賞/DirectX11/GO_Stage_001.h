//=============================================================================
//
// ステージ1 [GO_Stage_001.h]
// Author : Yanagisawa Yuta
//
// 説明：直方体
//=============================================================================
#pragma once
#include "GO_Stage.h"



class GO_Stage_001 :
    public GO_Stage
{
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    virtual int ReturnIndex() override {
        return STAGE_NUM_001;
    }

private:
    LIGHT* pLight;
};

