#pragma once
#include "Effect.h"
class E_SpeedUp :
    public Effect
{
private:
    char* m_pTexName = "data/TEXTURE/e_karashi.png";

    int m_numTime;
public:
    // Effect ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Initialize(void) override;

    virtual void Finalize(void) override;

    virtual void Update(void) override;

    virtual void Draw(void) override;

    void SetPos(D3DXVECTOR2 pos) { m_Vertex.pos = pos; }
};

