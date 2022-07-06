#pragma once
#include "Effect.h"
class E_Circle :
    public Effect
{
private:
    const float SIZE_ACCELERATION = 0.5f;
public:
    // Effect ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Initialize(void) override;
    virtual void Finalize(void) override;
    virtual void Update(void) override;
    virtual void Draw(void) override;

private:
    char* m_pTexName = "data/TEXTURE/circle_effect_noisecolor1.png";

    float m_AddSize;
};

