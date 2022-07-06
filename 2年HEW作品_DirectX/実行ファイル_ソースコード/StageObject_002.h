#pragma once
//=============================================================================
//
// ステージ選択画面オブジェクト_002 [StageObject_002.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "StageObject_001.h"
class StageObject_002 :
    public StageObject_001
{
public:
    virtual HRESULT Init(void) override;
    virtual void    Draw(void) override;
    virtual void ClickUpdate(void) override;
    virtual STAGE_NUM ReturnStageNum(void) override { return STAGE_NUM_002; }

private:
    char m_TextureName[64] = "data/TEXTURE/Select_Stage2.png";
    int  m_TextureIndex;
};

