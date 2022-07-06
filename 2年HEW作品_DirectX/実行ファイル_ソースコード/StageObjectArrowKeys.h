#pragma once
#include "StageObject.h"
class StageObjectArrowKeys  
{
public:
    //十字キー
    virtual bool IsArrowKeyTriggerd(void)= 0;
    virtual void Update_ArrowKeyTriggerd(void) = 0;

    //エンターキー
    virtual bool IsEnterKeyTriggerd(void) = 0;
    virtual void Update_EnterKeyTriggerd(void) = 0;


};

