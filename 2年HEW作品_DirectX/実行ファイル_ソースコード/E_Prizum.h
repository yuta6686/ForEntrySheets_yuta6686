#pragma once
#include "Effect.h"


class E_Prizum :
    public Effect
{
public:
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

private:
    

    char m_TexName[64] = "data/TEXTURE/Prizum_Effect.png";
};

