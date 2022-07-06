#pragma once
#include "StageObject.h"
class StageObjectMouse :
    public StageObject
{
public:
    // StageObject を介して継承されました
    virtual HRESULT Init(void) override =0;
    virtual void Uninit(void) override=0;
    virtual void Update(void) override=0;
    virtual void Draw(void) override=0;

    //クリック
    virtual bool IsClick(void)=0;
    virtual void ClickUpdate(void)=0;

    //マウスオーバー
    virtual bool IsMouseOver(void)=0;
    virtual void MouseOverUpdate(void)=0;

    virtual STAGE_NUM ReturnStageNum(void) override=0;
};

