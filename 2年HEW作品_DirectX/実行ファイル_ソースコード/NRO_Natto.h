#pragma once
#include "NattoRotateObject.h"
class NRO_Natto :
    public NattoRotateObject
{
public:
    NRO_Natto(char* texName) :NattoRotateObject(texName) {}

    // NattoRotateObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    virtual int GetGameScene(void) override;

};

