#pragma once
//=============================================================================
//
// ステージ選択画面オブジェクト_001 [StageObject_001.h]
// Author :	yuta yanagisawa 
//
//=============================================================================
#include "StageObject.h"
class StageObject_001 :
    public StageObject
{
public:
    StageObject_001() {};  

    // StageObject を介して継承されました
    virtual HRESULT Init(void) override;

    virtual void Uninit(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual bool IsClick(void) override;

    virtual void ClickUpdate(void) override;

    virtual bool IsMouseOver(void) override;

    virtual void MouseOverUpdate(void) override;

    virtual STAGE_NUM ReturnStageNum(void) override { return STAGE_NUM_001; }
protected:
    D3DXVECTOR2 m_MousePos;

private:
    char m_TextureName[64] = "data/TEXTURE/Select_Stage1.png";
    int  m_TextureIndex;

};

