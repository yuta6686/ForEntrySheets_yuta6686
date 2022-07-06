#pragma once
#include "Effect.h"
class E_AddTime :
    public Effect
{
private:
    char* m_TexName = "data/TEXTURE/plusten3.png";

    const float DECLEASE_ALPHA = 0.02f;
    const float ZOOM_VALUE = 2.0f;
public:
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

};

